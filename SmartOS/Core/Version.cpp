﻿#include "Type.h"
#include "DateTime.h"
#include "SString.h"

#include "Version.h"

/************************************************ Version ************************************************/

Version::Version()
{
	Major = 0;
	Minor = 0;
	Build = 0;
}

Version::Version(int value)
{
	Major = value >> 24;
	Minor = value >> 16;

	Build = value & 0xFFFF;
}

Version::Version(int major, int minor, int build)
{
	Major = major;
	Minor = minor;
	Build = build;

	// 有可能是 170325 这样的写法
	if (build > 120000) SetCompile(build);
}

Version::Version(const Version& ver)
{
	*this = ver;
}

Version::Version(Version&& ver)
{
	*this = ver;
}

Version& Version::operator=(const Version& ver)
{
	Major = ver.Major;
	Minor = ver.Minor;
	Build = ver.Build;

	return *this;
}

int Version::ToValue() const
{
	return (Major << 24) | (Minor << 16) | Build;
}

int Version::CompareTo(const Version& value) const
{
	int n = (int)Major - value.Major;
	if (n) return n;

	n = (int)Minor - value.Minor;
	if (n) return n;

	n = (int)Build - value.Build;
	if (n) return n;

	return 0;
}

bool operator==	(const Version& left, const Version& right) { return left.CompareTo(right) == 0; }
bool operator!=	(const Version& left, const Version& right) { return left.CompareTo(right) != 0; }
bool operator>	(const Version& left, const Version& right) { return left.CompareTo(right) > 0; }
bool operator<	(const Version& left, const Version& right) { return left.CompareTo(right) < 0; }
bool operator>=	(const Version& left, const Version& right) { return left.CompareTo(right) >= 0; }
bool operator<=	(const Version& left, const Version& right) { return left.CompareTo(right) <= 0; }

// 根据版本号反推编译时间
DateTime Version::Compile() const
{
	DateTime dt(2000, 1, 1);

	// Build 是2000-01-01以来的天数
	dt = dt.AddDays(Build);

	return dt;
}

Version& Version::SetCompile(int year, int month, int day)
{
	DateTime dt(2000, 1, 1);
	DateTime dt2(year, month, day);
	Build = (dt2 - dt).TotalDays();

	return *this;
}

// 设置编译日期 170325
Version& Version::SetCompile(int buildday)
{
	int day = buildday % 100;
	buildday /= 100;
	int month = buildday % 100;
	int year = buildday / 100 + 2000;

	DateTime dt(2000, 1, 1);
	DateTime dt2(year, month, day);
	Build = (dt2 - dt).TotalDays();

	return *this;
}

String Version::ToString() const
{
	String str;
	str = str + Major + '.' + Minor + '.' + Build;

	return str;
}
