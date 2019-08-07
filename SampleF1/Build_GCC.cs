// 本脚本文件需要安装XScript才能双击运行，下载后解压缩运行一次XScript.exe即可完成安装
// http://x.newlifex.com/XScript.zip

var build = Builder.Create("GCCArm");
build.Init(false);
build.CPU = "Cortex-M3";
build.Defines.Add("STM32F1");
build.AddIncludes("..\\SmartOS");
build.AddLibs("..\\Lib", "STM32F10x*.a");
build.AddLibs("..\\SmartOS", "SmartOS_M3?.a");
build.AddLibs("..\\SmartOS", "SmartOS_F1?.a");
build.AddFiles(".", "*.c;*.cpp");
build.CompileAll();
build.Build();

build.Debug = true;
build.CompileAll();
build.Build();
