// String.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <locale>
#include <cstring>
#include "../include/Core/String.h"

///////////////////
///   Methods   ///

String String::SubString(uint32 start, uint32 end) const
{
	if (start >= end || start >= this->Length())
	{
		return "";
	}

	return _value.Slice(start, end);
}

String String::ToUpper() const
{
	auto result = Array<Char>(this->Length());

	for (uint32 i = 0; i < this->Length(); ++i)
	{
		result.Add(std::toupper(this->CharAt(i), std::locale()));
	}

	return String(result);
}

String String::ToLower() const
{
	auto result = Array<Char>(this->Length());

	for (uint32 i = 0; i < this->Length(); ++i)
	{
		result.Add(std::tolower(this->CharAt(i), std::locale()));
	}

	return String(result);
}

bool String::StartsWith(const String& string) const
{
	for (uint32 i = 0; i < string.Length(); ++i)
	{
		if (this->CharAt(i) != string.CharAt(i))
		{
			return false;
		}
	}

	return true;
}

bool String::EndsWith(const String& string) const
{
	for (uint32 i = 1; i <= string.Length(); ++i)
	{
		if (this->CharAt(this->Length() - i) != string.CharAt(string.Length() - i))
		{
			return false;
		}
	}

	return true;
}

String String::RemovePadding(const String& string, bool front, bool back)
{
	uint32 start = 0;
	if (front)
	{
		while (string[start] == ' ')
		{
			++start;
		}
	}

	uint32 end = string.Length() - 1;
	if (back)
	{
		while (string[end] == ' ')
		{
			--end;
		}
	}

	return string.SubString(start, end + 1);
}

Array<uint32> String::OccurencesOf(const String& string) const
{
	Array<uint32> occurences;

	for (uint32 i = 0; i < this->Length(); ++i)
	{
		String comp = SubString(i, i + string.Length());
		if (comp == string)
		{
			occurences.Add(i);
		}
	}

	return occurences;
}

String String::Reverse() const
{
	Array<Char> result;

	for (int32 i = this->Length(); i > 0; --i)
	{
		result.Add(this->CharAt(i - 1));
	}

	return String(result);
}

uint32 String::Length(CString string)
{
	return static_cast<uint32>(strlen(string));
}

int32 String::Compare(const String& stringA, const String& stringB, bool caseSensitive)
{
	if (!caseSensitive)
	{
		return String::Compare(stringA.ToLower(), stringB.ToLower(), true);
	}

	return strcmp(stringA.Cstr(), stringB.Cstr());
}

/////////////////////
///   Operators   ///

String& String::operator=(CString rhs)
{
	_value = Array<Char>(rhs, this->Length(rhs) + 1);
	return *this;
}

String& String::operator=(Char rhs)
{
	_value.Reset(2);
	_value.Add(rhs);
	_value.Add('\0');
	return *this;
}

bool operator>(const String& lhs, const String& rhs)
{
	return String::Compare(lhs, rhs) > 0;
}

bool operator<(const String& lhs, const String& rhs)
{
	return String::Compare(lhs, rhs) < 0;
}

String operator+(const String& lhs, const String& rhs)
{
	Array<Char> result = lhs._value.Slice(0, lhs.Length()) + rhs._value.Slice(0, rhs.Length());
	return String(result);
}
