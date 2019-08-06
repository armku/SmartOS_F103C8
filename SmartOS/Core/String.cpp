﻿#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>

// gcc里面strncasecmp位于strings.h
#ifdef __GNUC__
#include <strings.h>
#endif

#include "_Core.h"

#include "ByteArray.h"

#include "SString.h"

char* utohex(uint value, byte size, char* string, bool upper);
#ifndef _MSC_VER
extern char* itoa(int value, char* string, int radix);
#endif
extern char* ltoa(Int64 value, char* string, int radix);
extern char* utoa(uint value, char* string, int radix);
extern char* ultoa(UInt64 value, char* string, int radix);
char* dtostrf(double val, byte prec, char* sout, int len);


/******************************** String ********************************/

String::String(cstring cstr) : Array(Arr, ArrayLength(Arr))
{
	init();

	_Length = cstr ? strlen(cstr) : 0;
	if (_Length)
	{
		_Arr = (char*)cstr;
		// 此时保证外部一定是0结尾
		_Capacity = _Length + 1;
		_canWrite = false;
	}
}

String::String(const String& value) : Array(Arr, ArrayLength(Arr))
{
	init();
	*this = value;
}

String::String(String&& rval) : Array(Arr, ArrayLength(Arr))
{
	init();
	move(rval);
}

String::String(bool value) : Array(Arr, ArrayLength(Arr))
{
	init();

	Concat(value);
}

String::String(char c) : Array(Arr, ArrayLength(Arr))
{
	init();

	_Arr[0] = c;
	_Arr[1] = 0;
	_Length = 1;
}

String::String(byte value, int radix) : Array(Arr, ArrayLength(Arr))
{
	init();

	Concat(value, radix);
}

String::String(short value, int radix) : Array(Arr, ArrayLength(Arr))
{
	init();

	Concat(value, radix);
}

String::String(ushort value, int radix) : Array(Arr, ArrayLength(Arr))
{
	init();

	Concat(value, radix);
}

String::String(int value, int radix) : Array(Arr, ArrayLength(Arr))
{
	init();

	Concat(value, radix);
}

String::String(uint value, int radix) : Array(Arr, ArrayLength(Arr))
{
	init();

	Concat(value, radix);
}

String::String(Int64 value, int radix) : Array(Arr, ArrayLength(Arr))
{
	init();

	Concat(value, radix);
}

String::String(UInt64 value, int radix) : Array(Arr, ArrayLength(Arr))
{
	init();

	Concat(value, radix);
}

String::String(float value, int decimalPlaces) : Array(Arr, ArrayLength(Arr))
{
	init();

	Concat(value, decimalPlaces);
}

String::String(double value, int decimalPlaces) : Array(Arr, ArrayLength(Arr))
{
	init();

	Concat(value, decimalPlaces);
}

// 外部传入缓冲区供内部使用，内部计算字符串长度，注意长度减去零结束符
String::String(char* str, int length) : Array(str, length)
{
	_Arr = str;
	_Capacity = length - 1;

	// 计算外部字符串长度
	//int len = strlen(str);
	//if (len >= length) len = length - 1;

	auto p = str;
	int len = 0;
	while (*p++ != '\0' && len < _Capacity) len++;

	_Length = len;
	_Arr[len] = '\0';
}

// 外部传入缓冲区供内部使用，内部计算字符串长度，注意长度减去零结束符
String::String(char* str, int length, bool expand) : String(str, length)
{
	Expand = expand;
}

// 包装静态字符串，直接使用，修改时扩容
String::String(cstring str, int length) : Array((char*)str, length)
{
	// 此时不能保证外部一定是0结尾
	_Capacity = length + 1;
	_canWrite = false;
}

inline void String::init()
{
	_Arr = Arr;
	_Capacity = sizeof(Arr) - 1;
	_Length = 0;
	_Arr[0] = '\0';
}

void String::release()
{
	Array::Release();

	init();
}

bool String::CheckCapacity(int size)
{
	int old = _Capacity;
	CheckCapacity(size + 1, _Length);
	if (old == _Capacity) return true;

	// 强制最后一个字符为0
	_Arr[_Length] = '\0';

	_Capacity--;

	return true;
}

void* String::Alloc(int len)
{
	if (len <= (int)sizeof(Arr))
	{
		_needFree = false;
		return Arr;
	}
	else
	{
		_needFree = true;
		return new byte[len];
	}
}

String& String::copy(cstring cstr, int length)
{
	if (!cstr || !length) return *this;

	if (!CheckCapacity(length))
		release();
	else
	{
		_Length = length;
		//strcpy(_Arr, cstr);
		//!!! 特别注意要拷贝的长度
		if (length) Buffer(_Arr, _Capacity).Copy(0, cstr, length);
		_Arr[length] = '\0';
	}

	return *this;
}

void String::move(String& rhs)
{
	/*
	move逻辑：
	1，如果右值是内部指针，则必须拷贝数据，因为右值销毁的时候，内部数据跟着释放
	2，如果右值是外部指针，并且需要释放，则直接拿指针过来使用，由当前对象负责释放
	3，如果右值是外部指针，而不需要释放，则拷贝数据，因为那指针可能是借用外部的栈内存
	*/

	if (rhs._Arr != rhs.Arr && rhs._needFree)
	{
		Array::move(rhs);

		return;
	}

	SetLength(rhs.Length());
	copy(rhs._Arr, rhs._Length);
}

// 修改时拷贝
bool String::CopyOrWrite()
{
	// 如果不可写
	if (!_canWrite) return CheckCapacity(_Length);

	return false;
}

bool String::SetLength(int len, bool bak)
{
	//if(!Array::SetLength(length, bak)) return false;
	// 字符串的最大长度为容量减一，因为需要保留一个零结束字符
	if (len < _Capacity)
	{
		_Length = len;
	}
	else
	{
		if (!CheckCapacity(len + 1, bak ? _Length : 0)) return false;
		// 扩大长度
		if (len > _Length) _Length = len;
	}

	_Arr[_Length] = '\0';

	return true;
}

// 拷贝数据，默认-1长度表示当前长度
int String::Copy(int destIndex, const void* src, int len)
{
	int rs = Buffer::Copy(destIndex, src, len);
	if (!rs) return 0;

	_Arr[_Length] = '\0';

	return rs;
}

// 把数据复制到目标缓冲区，默认-1长度表示当前长度
int String::CopyTo(int srcIndex, void* dest, int len) const
{
	int rs = Buffer::CopyTo(srcIndex, dest, len);
	if (!rs) return 0;

	((char*)dest)[rs] = '\0';

	return rs;
}

String& String::operator = (const String& rhs)
{
	if (this == &rhs) return *this;

	if (rhs._Arr) copy(rhs._Arr, rhs._Length);
	else release();

	return *this;
}

String& String::operator = (String&& rval)
{
	if (this != &rval) move(rval);
	return *this;
}

String& String::operator = (cstring cstr)
{
	if (cstr) copy(cstr, strlen(cstr));
	else release();

	return *this;
}

bool String::Concat(const Object& obj)
{
	return Concat(obj.ToString());
}

bool String::Concat(const String& s)
{
	return Concat(s._Arr, s._Length);
}

bool String::Concat(cstring cstr, int length)
{
	if (!cstr) return false;
	if (length == 0) return true;

	int newlen = _Length + length;
	if (!CheckCapacity(newlen)) return false;

	//strcpy(_Arr + _Length, cstr);
	Buffer(_Arr, _Capacity).Copy(_Length, cstr, length);
	_Length = newlen;
	_Arr[_Length] = '\0';

	return true;
}

bool String::Concat(cstring cstr)
{
	if (!cstr) return 0;
	return Concat(cstr, strlen(cstr));
}

bool String::Concat(bool value)
{
	return Concat(value ? "true" : "false");
}

bool String::Concat(char c)
{
	if (!CheckCapacity(_Length + 1)) return false;

	_Arr[_Length++] = c;

	return true;
}

bool String::Concat(byte num, int radix)
{
	// 十六进制固定长度
	if (radix == 16 || radix == -16)
	{
		if (!CheckCapacity(_Length + (sizeof(num) << 1))) return false;

		utohex(num, sizeof(num), _Arr + _Length, radix < 0);
		_Length += (sizeof(num) << 1);

		return true;
	}

	char buf[1 + 3 * sizeof(byte)];
#if defined(_MSC_VER)
	_itoa_s(num, buf, sizeof(buf), radix);
#else
	itoa(num, buf, radix);
#endif

	return Concat(buf, strlen(buf));
}

bool String::Concat(short num, int radix)
{
	// 十六进制固定长度
	if (radix == 16 || radix == -16) return Concat((ushort)num, radix);

	char buf[2 + 3 * sizeof(int)];
#if defined(_MSC_VER)
	_itoa_s(num, buf, sizeof(buf), radix);
#else
	itoa(num, buf, radix);
#endif
	return Concat(buf, strlen(buf));
}

bool String::Concat(ushort num, int radix)
{
	// 十六进制固定长度
	if (radix == 16 || radix == -16)
	{
		if (!CheckCapacity(_Length + (sizeof(num) << 1))) return false;

		utohex(num, sizeof(num), _Arr + _Length, radix < 0);
		_Length += (sizeof(num) << 1);

		return true;
	}

	char buf[2 + 3 * sizeof(int)];
	utoa(num, buf, radix);
	return Concat(buf, strlen(buf));
}

bool String::Concat(int num, int radix)
{
	// 十六进制固定长度
	if (radix == 16 || radix == -16) return Concat((uint)num, radix);

	char buf[2 + 3 * sizeof(int)];
#if defined(_MSC_VER)
	_itoa_s(num, buf, sizeof(buf), radix);
#else
	itoa(num, buf, radix);
#endif
	return Concat(buf, strlen(buf));
}

bool String::Concat(uint num, int radix)
{
	// 十六进制固定长度
	if (radix == 16 || radix == -16)
	{
		if (!CheckCapacity(_Length + (sizeof(num) << 1))) return false;

		utohex(num, sizeof(num), _Arr + _Length, radix < 0);
		_Length += (sizeof(num) << 1);

		return true;
	}

	char buf[1 + 3 * sizeof(uint)];
	utoa(num, buf, radix);
	return Concat(buf, strlen(buf));
}

bool String::Concat(Int64 num, int radix)
{
	// 十六进制固定长度
	if (radix == 16 || radix == -16) return Concat((UInt64)num, radix);

	char buf[2 + 3 * sizeof(Int64)];
	ltoa(num, buf, radix);
	return Concat(buf, strlen(buf));
}

bool String::Concat(UInt64 num, int radix)
{
	// 十六进制固定长度
	if (radix == 16 || radix == -16)
	{
		if (!CheckCapacity(_Length + (sizeof(num) << 1))) return false;

		utohex((int)(num >> 32), sizeof(num) >> 1, _Arr + _Length, radix < 0);
		_Length += sizeof(num);
		utohex((int)(num & 0xFFFFFFFF), sizeof(num) >> 1, _Arr + _Length, radix < 0);
		_Length += sizeof(num);

		return true;
	}

	char buf[1 + 3 * sizeof(UInt64)];
	ultoa(num, buf, radix);
	return Concat(buf, strlen(buf));
}

static char* ftoa(char* str, int len, double num, int prec)
{
	// 先计算整数部分，连符号一起计算了
	// 在逐级计算小数点后
	int n = (int)num;
	num -= n;
	if (num < 0)num = -num;

	// 整数部分
	ltoa((Int64)n, str, 10);

	if (prec > 0 && num > 0.0)
	{
		// 小数部分
		int slen = strlen(str);
		int m = 10;
		while (--prec > 0) m *= 10;

		str[slen++] = '.';
		ltoa((Int64)(m*num), str + slen, 10);
		slen = strlen(str);
		/*for (int i = 0; i < prec; i++)
		{
			num *= 10;
			n = (int)num;
			num -= n;
			str[slen++] = '0' + n;
		}
		str[slen] = 0;*/

		// 干掉后面多余的0
		for (int i = slen - 1; i >= 0 && str[i] == '0'; i--, slen--)
		{
			str[i] = '\0';
		}
		if (str[slen - 1] == '.') str[slen - 1] = '\0';
	}

	return str;
}

bool String::Concat(float num, int decimalPlaces)
{
	char buf[20];
	//dtostrf(num, decimalPlaces, buf, sizeof(buf));
	//sprintf(buf, "%f", num);
	ftoa(buf, sizeof(buf), num, decimalPlaces);
	return Concat(buf, strlen(buf));
}

bool String::Concat(double num, int decimalPlaces)
{
	char buf[20];
	//dtostrf(num, decimalPlaces, buf, sizeof(buf));
	//sprintf(buf, "%f", num);
	ftoa(buf, sizeof(buf), num, decimalPlaces);
	return Concat(buf, strlen(buf));
}

int String::CompareTo(const String& s) const
{
	return CompareTo(s._Arr, s._Length, false);
}

#ifdef _MSC_VER
#define strncasecmp _strnicmp
#endif
int String::CompareTo(cstring cstr, int len, bool ignoreCase) const
{
	if (len < 0) len = strlen(cstr);
	if (!_Arr)
	{
		if (cstr && len > 0) return -1;
		return 0;
	}
	if (!cstr && _Arr && _Length > 0) return 1;

	// 小心越界
	int len2 = len;
	if (len2 > _Length) len2 = _Length;

	// 逐个比较字符，直到指定长度或者源字符串结束
	int rs = 0;
	if (ignoreCase)
		rs = strncasecmp(_Arr, cstr, len2);
	else
		rs = strncmp(_Arr, cstr, len2);

	// 如果不等，直接返回
	if (rs != 0)return rs;

	// 如果相等，则还要考虑没有比较部分
	if (len > len2) return -1;
	if (_Length > len2) return 1;

	return 0;
}

bool String::Equals(const String& str) const
{
	return _Length == str._Length && CompareTo(str._Arr, str._Length, false) == 0;
}

bool String::Equals(cstring cstr) const
{
	int len = strlen(cstr);
	if (len != _Length) return false;

	return CompareTo(cstr, len, false) == 0;
}

bool String::EqualsIgnoreCase(const String &str) const
{
	return _Length == str._Length && CompareTo(str._Arr, str._Length, true) == 0;
}

bool String::EqualsIgnoreCase(cstring cstr) const
{
	int len = strlen(cstr);
	if (len != _Length) return false;

	return CompareTo(cstr, len, true) == 0;
}

bool String::operator<(const String& rhs) const
{
	return CompareTo(rhs) < 0;
}

bool String::operator>(const String& rhs) const
{
	return CompareTo(rhs) > 0;
}

bool String::operator<=(const String& rhs) const
{
	return CompareTo(rhs) <= 0;
}

bool String::operator>=(const String& rhs) const
{
	return CompareTo(rhs) >= 0;
}

/*void String::SetAt(int loc, char c)
{
	if (loc < _Length) _Arr[loc] = c;
}*/

char& String::operator[](int index)
{
	static char dummy_writable_char;
	if (index >= _Length || !_Arr) {
		dummy_writable_char = 0;
		return dummy_writable_char;
	}

	// 修改时拷贝
	CopyOrWrite();

	return _Arr[index];
}

char String::operator[](int index) const
{
	if (index >= _Length || !_Arr) return 0;
	return _Arr[index];
}

void String::GetBytes(byte* buf, int bufsize, int index) const
{
	if (!bufsize || !buf) return;
	if (index >= _Length) {
		buf[0] = 0;
		return;
	}
	int n = bufsize;
	if (n > _Length - index) n = _Length - index;
	//strncpy((char*)buf, _Arr + index, n);
	Buffer(buf, bufsize).Copy(0, _Arr + index, n);
	//buf[n] = '\0';
}

ByteArray String::GetBytes() const
{
	ByteArray bs;
	bs.SetLength(_Length);

	GetBytes(bs.GetBuffer(), bs.Length());

	return bs;
}

ByteArray String::ToHex() const
{
	ByteArray bs;
	bs.SetLength(_Length / 2);

	char cs[3];
	cs[2] = 0;
	byte* b = bs.GetBuffer();
	auto p = _Arr;
	int n = 0;
	for (int i = 0; i < _Length; i += 2)
	{
		cs[0] = *p++;
		cs[1] = *p++;

		*b++ = (byte)strtol(cs, nullptr, 16);

		// 过滤横杠和空格
		if (*p == '-' || isspace(*p))
		{
			p++;
			i++;
		}

		n++;
	}
	bs.SetLength(n);

	return bs;
}

int String::ToInt() const
{
	if (_Length == 0) return 0;

	if (_Arr[_Length] == '\0') return atoi(_Arr);

	// 非零结尾字符串需要特殊处理
	String s;
	s.copy(_Arr, _Length);
	return s.ToInt();
}

float String::ToFloat() const
{
	if (_Length == 0) return 0;

	if (_Arr[_Length] == '\0') return (float)atof(_Arr);

	// 非零结尾字符串需要特殊处理
	String s;
	s.copy(_Arr, _Length);
	return s.ToFloat();
}

double String::ToDouble() const
{
	if (_Length == 0) return 0;

	if (_Arr[_Length] == '\0') return atof(_Arr);

	// 非零结尾字符串需要特殊处理
	String s;
	s.copy(_Arr, _Length);
	return s.ToDouble();
}

// 输出对象的字符串表示方式
String& String::ToStr(String& str) const
{
	// 把当前字符串复制到目标字符串后面
	//str.Copy(*this, str._Length);
	str += *this;

	return (String&)*this;
}

// 输出对象的字符串表示方式
String String::ToString() const
{
	return *this;
}

// 调试输出字符串
void String::Show(bool newLine) const
{
	//if(_Length) debug_printf("%s", _Arr);
	for (int i = 0; i < _Length; i++)
	{
		//fput(_Arr[i]);
		debug_printf("%c", _Arr[i]);
	}
	if (newLine) debug_printf("\r\n");
}

// 格式化字符串，输出到现有字符串后面。方便我们连续格式化多个字符串
String& String::Format(cstring format, ...)
{
	va_list ap;

	va_start(ap, format);

	// 无法准确估计长度，大概乘以2处理
	CheckCapacity(_Length + (strlen(format) << 1));

	//char* p = _Arr;
	int len2 = vsnprintf(_Arr + _Length, _Capacity - _Length, format, ap);
	_Length += len2;

	va_end(ap);

	return *this;
}

int String::IndexOf(const char ch, int startIndex) const
{
	if (startIndex < 0) return -1;
	if (startIndex >= _Length) return -1;

	for (int i = startIndex; i < _Length; i++)
	{
		if (_Arr[i] == ch) return i;
	}

	return -1;
}

int String::IndexOf(const String& str, int startIndex) const
{
	return Search(str._Arr, str._Length, startIndex, false);
}

int String::IndexOf(cstring str, int startIndex) const
{
	return Search(str, strlen(str), startIndex, false);
}

int String::LastIndexOf(const char ch, int startIndex) const
{
	if (startIndex >= _Length) return -1;

	for (int i = _Length - 1; i >= startIndex; i--)
	{
		if (_Arr[i] == ch) return i;
	}
	return -1;
}

int String::LastIndexOf(const String& str, int startIndex) const
{
	return Search(str._Arr, str._Length, startIndex, true);
}

int String::LastIndexOf(cstring str, int startIndex) const
{
	return Search(str, strlen(str), startIndex, true);
}

int String::Search(cstring str, int len, int startIndex, bool rev) const
{
	if (!str) return -1;
	if (startIndex < 0) return -1;

	// 可遍历的长度
	int count = _Length - len;
	if (startIndex > count) return -1;

	// 遍历源字符串
	auto s = _Arr + startIndex;
	auto e = _Arr + _Length - 1;
	auto p = rev ? e : s;
	for (int i = 0; i <= count; i++)
	{
		// 最大比较个数以目标字符串为准，源字符串确保长度足够
		if (strncmp(p, str, len) == 0) return p - _Arr;

		if (rev)
		{
			if (--p < s) break;
		}
		else
		{
			if (++p > e) break;
		}
	}
	return -1;
}

bool String::Contains(const String& str) const { return IndexOf(str) >= 0; }

bool String::Contains(cstring str) const { return IndexOf(str) >= 0; }

bool String::StartsWith(const String& str, int startIndex) const
{
	if (!_Arr || !str._Arr) return false;
	if (str._Length == 0) return false;
	if (startIndex + str._Length > _Length) return false;

	return strncmp(&_Arr[startIndex], str._Arr, str._Length) == 0;
}

bool String::StartsWith(cstring str, int startIndex) const
{
	if (!_Arr || !str) return false;
	int slen = strlen(str);
	if (slen == 0) return false;
	if (startIndex + slen > _Length) return false;

	return strncmp(&_Arr[startIndex], str, slen) == 0;
}

bool String::EndsWith(const String& str) const
{
	if (!_Arr || !str._Arr) return false;
	if (str._Length == 0) return false;
	if (str._Length > _Length) return false;

	return strncmp(&_Arr[_Length - str._Length], str._Arr, str._Length) == 0;
}

bool String::EndsWith(cstring str) const
{
	if (!_Arr || !str) return false;
	int slen = strlen(str);
	if (slen == 0) return false;
	if (slen > _Length) return false;

	return strncmp(&_Arr[_Length - slen], str, slen) == 0;
}

StringSplit String::Split(const String& sep) const
{
	return StringSplit(*this, sep.GetBuffer());
}

StringSplit String::Split(cstring sep) const
{
	return StringSplit(*this, sep);
}

String String::Substring(int start, int len) const
{
	/*String str;

	if (len < 0) len = _Length - start;
	if (_Length && start < _Length) str.copy(_Arr + start, len);

	return str;*/

	if (len < 0) len = _Length - start;
	if (len > _Length - start) len = _Length - start;

	return String((cstring)(_Arr + start), len);
}

cstring trim(cstring str, int& len, bool trimBegin, bool trimEnd)
{
	if (!str || len == 0) return str;

	auto s = str;
	if (trimBegin) while (isspace(*s)) s++;

	auto e = str + len - 1;
	if (trimEnd) while (isspace(*e) && e >= s) e--;

	len = e + 1 - s;
	//if (s > str && len) Buffer(str, len) = s;
	//str[len] = 0;

	return s;
}

String String::TrimStart() const
{
	/*String str(*this);
	trim(str._Arr, str._Length, true, false);

	return str;*/

	int len = _Length;
	auto str = trim(_Arr, len, true, false);

	return String(str, len);
}

String String::TrimEnd() const
{
	/*String str(*this);
	trim(str._Arr, str._Length, false, true);

	return str;*/

	int len = _Length;
	auto str = trim(_Arr, len, false, true);

	return String(str, len);
}

String String::Trim() const
{
	/*String str(*this);
	trim(str._Arr, str._Length, true, true);

	return str;*/

	int len = _Length;
	auto str = trim(_Arr, len, true, true);

	return String(str, len);
}

String String::Replace(char find, char replace) const
{
	String str(*this);

	auto p = (char*)str.GetBuffer();
	for (int i = 0; i < Length(); i++, p++)
	{
		if (*p == find) *p = replace;
	}

	return str;
}

String String::ToLower() const
{
	String str(*this);
	auto p = str._Arr;
	for (int i = 0; i < str._Length; i++)
		p[i] = tolower(p[i]);

	return str;
}

String String::ToUpper() const
{
	String str(*this);
	auto p = str._Arr;
	for (int i = 0; i < str._Length; i++)
		p[i] = toupper(p[i]);

	return str;
}

// 静态比较器。比较两个字符串指针
int String::Compare(const void* v1, const void* v2)
{
	if (!v1) return v1 == v2 ? 0 : -1;
	if (!v2) return 1;

	auto str1 = (cstring)v1;
	auto str2 = (cstring)v2;
	return strncmp((char*)v1, str2, strlen(str1));
}

/******************************** 辅助 ********************************/

#ifndef _MSC_VER
extern char* itoa(int value, char *string, int radix)
{
	return ltoa(value, string, radix);
}

extern char* ltoa(Int64 value, char* string, int radix)
{
	char tmp[33];
	char *tp = tmp;
	Int64 i;
	UInt64 v;
	int sign;
	char *sp;

	if (string == nullptr) return 0;

	if (radix > 36 || radix <= 1) return 0;

	sign = (radix == 10 && value < 0);
	if (sign)
		v = -value;
	else
		v = (UInt64)value;

	while (v || tp == tmp)
	{
		i = v % radix;
		v = v / radix;
		if (i < 10)
			*tp++ = i + '0';
		else
			*tp++ = i + 'a' - 10;
	}

	sp = string;

	if (sign) *sp++ = '-';
	while (tp > tmp)
		*sp++ = *--tp;
	*sp = 0;

	return string;
}
#endif

char* utohex(uint value, byte size, char* string, bool upper)
{
	if (string == nullptr) return 0;

	// 字节数乘以2是字符个数
	size <<= 1;
	// 指针提前指向最后一个字符，数字从小往大处理，字符需要倒过来赋值
	auto tp = string + size;;
	*tp-- = '\0';
	char ch = upper ? 'A' : 'a';
	for (int i = 0; i < size; i++)
	{
		byte bt = value & 0x0F;
		value >>= 4;
		if (bt < 10)
			*tp-- = bt + '0';
		else
			*tp-- = bt + ch - 10;
	}

	return string;
}

#ifndef _MSC_VER
extern char* utoa(uint value, char* string, int radix)
{
	return ultoa(value, string, radix);
}

extern char* ultoa(UInt64 value, char* string, int radix)
{
	if (string == nullptr) return 0;

	if (radix > 36 || radix <= 1) return 0;

	char tmp[33];
	auto tp = tmp;
	auto v = value;
	char ch = radix < 0 ? 'A' : 'a';
	while (v || tp == tmp)
	{
		auto i = v % radix;
		v = v / radix;
		if (i < 10)
			*tp++ = i + '0';
		else
			*tp++ = i + ch - 10;
	}

	auto sp = string;
	while (tp > tmp)
		*sp++ = *--tp;
	*sp = '\0';

	return string;
}
#endif

char *dtostrf(double val, byte prec, char* str, int len)
{
	char fmt[20];
#if defined(_MSC_VER)
	sprintf_s(fmt, sizeof(fmt), "%%.%df", prec);
	len = sprintf_s(str, len, fmt, val);
#else
	sprintf(fmt, "%%.%df", prec);
	len = sprintf(str, fmt, val);
#endif

	// 干掉后面多余的0
	for (int i = len; i >= 0; i--)
	{
		if (str[i] == '0') str[i] = '\0';
	}

	return str;
}

/******************************** StringSplit ********************************/

StringSplit::StringSplit(const String& str, cstring sep) :
	_Str(str)
{
	Sep = sep;
	Position = -1;
	Length = 0;

	// 先算好第一段
	//int p	= _Str.IndexOf(_Sep);
	//if(p >= 0) _Length	= p;
}

const String StringSplit::Next()
{
	cstring ptr = nullptr;
	int len = 0;

	if (Position >= -1 && Sep)
	{
		String sp = Sep;

		// 从当前段之后开始找一段
		int s = Position + Length;
		// 除首次以外，每次都要跳过分隔符
		if (s < 0)
			s = 0;
		else
			s += sp.Length();

		// 检查是否已经越界
		if (s >= _Str.Length())
		{
			Position = -2;
			Length = 0;
		}
		else
		{
			// 查找分隔符
			int p = _Str.IndexOf(Sep, s);

			int sz = 0;
			// 剩余全部长度，如果找不到下一个，那么这个就是最后长度。不用跳过分隔符
			if (p < 0)
				sz = _Str.Length() - s;
			else
				sz = p - s;

			Position = s;
			Length = sz;

			ptr = _Str.GetBuffer() + Position;
			len = Length;
		}
	}

	// 包装一层指针
	return String(ptr, len);
}
