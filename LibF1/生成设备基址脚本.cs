using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using NewLife.Log;
using NewLife.Reflection;

namespace MxParser
{
    class Program
    {
        static void Main(string[] args)
        {
            XTrace.UseConsole();

            try
            {
                ProcessF10x();
            }
            catch (Exception ex)
            {
                XTrace.WriteException(ex);
            }
        }

        static void ProcessF10x()
        {
            var file = "stm32f0xx.h";
            if (!File.Exists(file)) file = "stm32f10x.h";
            if (!File.Exists(file)) file = "stm32f4xx.h";
            if (!File.Exists(file)) file = @"..\Src\stm32f10x.h";

            var dic = new Dictionary<String, DefItem>();
            ProcessFile(file, dic);
        }

        static void ProcessFile(String file, IDictionary<String, DefItem> dic)
        {
            if (file.IsNullOrEmpty() || !File.Exists(file)) return;

            var lines = File.ReadAllLines(file);
            foreach (var item in lines)
            {
                if (item.IsNullOrEmpty()) continue;

                var line = item.Trim();
                if (line.StartsWith("#include"))
                {

                }
                else if (line.StartsWith("#define"))
                {
                    line = line.Substring("#define".Length).Trim();
                    //Console.WriteLine(line);

                    var di = DefItem.Parse(line);
                    if (di != null) dic[di.Name] = di;
                }
            }

            // 执行表达式计算
            foreach (var item in dic)
            {
                if (item.Value.IsInt) continue;

                Console.WriteLine(item.Value);
                if (item.Value.Execute(dic))
                    Console.WriteLine(item.Value);
            }

            var sb = new StringBuilder();
            foreach (var item in dic)
            {
                var di = item.Value;
                if (!di.IsInt) continue;
                // 只要有Class的
                if (di.Class.IsNullOrEmpty()) continue;

                //Console.WriteLine(item.Value);
                //File.AppendAllText(idc, item.Value + Environment.NewLine);
                sb.AppendFormat("\tMakeName\t(0x{0:X8}, \"{1}\"\r\n", di.IntValue, di.Name);
                if (!di.Comment.IsNullOrEmpty())
                    sb.AppendFormat("\tMakeRptCmt\t(0x{0:X8}, \"{1}\"\r\n", di.IntValue, di.Comment);
                if (!di.Class.IsNullOrEmpty())
                    sb.AppendFormat("\tMakeStruct\t(0x{0:X8}, \"{1}\"\r\n", di.IntValue, di.Class);
            }
            var idc = Path.ChangeExtension(file, ".idc");
            File.WriteAllText(idc, sb.ToString());
        }

        class DefItem
        {
            public String Name;
            public String Value;
            public String Comment;
            public String Class;
            public String OriValue;

            public static DefItem Parse(String line)
            {
                var p = line.IndexOf(" ");
                if (p < 0) p = line.IndexOf("\t");
                if (p <= 0) return null;

                var di = new DefItem();
                di.Name = line.Substring(0, p);

                // 必须是标准名称
                if (!Regex.IsMatch(di.Name, "^\\w+$")) return null;

                line = line.Substring(p).Trim();

                // 分离注释，有两种
                if (line.EndsWith("*/") || line.Contains("/*"))
                {
                    p = line.IndexOf("/*");
                    if (p == 0) return null;
                    if (p < 0) return null;

                    di.Value = line.Substring(0, p).Trim();
                    di.Comment = line.Substring(p + 2).TrimEnd("*/").Trim();
                }
                else if (line.Contains("//"))
                {
                    p = line.IndexOf("//");
                    if (p == 0) return null;
                    if (p < 0) return null;

                    di.Value = line.Substring(0, p).Trim();
                    di.Comment = line.Substring(p + 2).Trim();
                }
                else
                {
                    di.Value = line;
                }

                di.Trim();

                // 如果斜杠结尾，说明有几行，放弃
                if (di.Value.EndsWith("\\")) return null;

                di.ParseClass();

                di.OriValue = di.Value;

                return di;
            }

            void Trim()
            {
                // 去掉Value前后的括号和双引号
                while (!Value.IsNullOrEmpty())
                {
                    var f = false;
                    if (Value.StartsWith("(") && Value.EndsWith(")"))
                    {
                        f = true;
                        Value = Value.Substring(1, Value.Length - 1 - 1);
                    }
                    if (Value.StartsWith("\"") && Value.EndsWith("\""))
                    {
                        f = true;
                        Value = Value.Substring(1, Value.Length - 1 - 1);
                    }
                    if (!f) break;
                }

                if (!Value.IsNullOrEmpty()) Value = Value.TrimStart(",", " ", "(uint32_t)", "(uint16_t)", "(uint8_t)").Trim();

                if (!Comment.IsNullOrEmpty()) Comment = Comment.TrimStart("!<").Trim();
            }

            void ParseClass()
            {
                if (Value.StartsWith("(") && Value.Contains(")"))
                {
                    Class = Value.Substring("(", ")").Trim().TrimEnd("*").Trim();
                    Value = Value.Substring(")").Trim();
                }
            }

            public Boolean IsInt
            {
                get
                {
                    var str = Value;
                    if (str.StartsWithIgnoreCase("0x"))
                    {
                        try
                        {
                            var n = Convert.ToInt32(str, 16);
                            return true;
                        }
                        catch
                        {
                            return false;
                        }
                    }
                    else
                    {
                        var n = 0;
                        return Int32.TryParse(str, out n);
                    }
                }
            }

            public UInt32 IntValue
            {
                get
                {
                    var str = Value;
                    if (str.StartsWithIgnoreCase("0x"))
                    {
                        try
                        {
                            return (UInt32)Convert.ToInt32(str, 16);
                        }
                        catch
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        var n = 0u;
                        if (!UInt32.TryParse(str, out n)) return 0;
                        return n;
                    }
                }
            }

            public Boolean Execute(IDictionary<String, DefItem> dic)
            {
                // 如果自己本身就是整数，没必要计算
                if (IsInt) return false;

                var str = Value;
                var reg = new Regex(@"(\w+)");
                str = reg.Replace(str, m =>
                {
                    var name = m.Groups[1].Value;

                    DefItem di;
                    if (!dic.TryGetValue(name, out di)) return name;
                    if (di == this) return name;

                    return di.Value;
                });

                if (str == Value) return false;

                // 简单替换后直接就是整数
                Value = str;
                if (IsInt) return true;

                // 执行整型计算
                try
                {
                    var rs = ScriptEngine.Execute(str);
                    if (rs is Int32)
                        Value = "0x" + ((Int32)rs).ToString("X8");
                    else if (rs is UInt32)
                        Value = "0x" + ((UInt32)rs).ToString("X8");
                }
                catch (Exception ex)
                {
                    XTrace.WriteException(ex);
                }

                return true;
            }

            public override string ToString()
            {
                var sb = new StringBuilder();
                sb.Append(Name);
                sb.Append("\t");
                if (!Class.IsNullOrEmpty()) sb.AppendFormat("({0}*)", Class);
                sb.Append(Value);
                if (!Comment.IsNullOrEmpty()) sb.AppendFormat("\t// {0}", Comment);

                return sb.ToString();
            }
        }
    }
}