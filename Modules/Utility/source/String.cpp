// string.cpp

#include <cstring>
#include <string>
#include <ctype.h>
#include "..\include\Utility\Math\Math.h"
#include "..\include\Utility\String.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

String::String(const char* value)
	: _value(nullptr)
{
	this->_value = new char[String::Length(value) + 1];
	strcpy(_value, value);
}

String::String(const String& copy)
	: _value(nullptr)
{
	this->_value = new char[copy.Length() + 1];
	strcpy(_value, copy._value);
}

String::String(String&& other)
	: _value(nullptr)
{
	_value = other._value;
	other._value = nullptr;
}

String::~String()
{
	delete[] _value;
}

///////////////////
///   Methods   ///

bool String::IsNullOrEmpty() const
{
	return _value == nullptr || this->Length() == 0;
}

uint32 String::Length() const
{
	return String::Length(_value);
}

const char* String::Cstr() const
{
	return _value;
}

String String::SubString(uint32 start) const
{
	return this->SubString(start, (uint32)this->Length());
}

String String::SubString(uint32 start, uint32 end) const
{
	String str;
	if (start >= end || start >= this->Length())
	{
		// Return an empty string
		return str;
	}

	char* string = new char[end - start + 1];
	for (uint32 i = 0; i < end - start; i++)
	{
		string[i] = _value[i + start];
	}
	string[end - start] = '\0';

	str = string;
	delete[] string;
	return str;
}

String String::ToUpper() const
{
	String str = This;

	for (uint32 i = 0; i < str.Length(); i++)
	{
		str._value[i] = toupper(str._value[i]);
	}

	return str;
}

String String::ToLower() const
{
	String str = This;

	for (uint32 i = 0; i < str.Length(); i++)
	{
		str._value[i] = tolower(str._value[i]);
	}

	return str;
}

List<uint32> String::OccurencesOf(const String& string) const
{
	List<uint32> occurences;

	for (uint32 i = 0; i < this->Length(); i++)
	{
		String comp = this->SubString(i, (uint32)string.Length() + i);
		if (comp == string)
		{
			occurences.Add(i);
		}
	}

	return occurences;
}

String String::GetFileExtension(const String& path)
{
	auto occurences = path.OccurencesOf(".");
	if (!occurences.IsEmpty())
	{
		return path.SubString(occurences.Last() + 1);
	}
	else
	{
		return "";
	}
}

String String::GetFileName(const String& path)
{
	String name = path;

	auto forwardSlashes = name.OccurencesOf("/");
	auto backSlashes = name.OccurencesOf("\\");

	if (!forwardSlashes.IsEmpty())
	{
		if (!backSlashes.IsEmpty())
		{
			name = name.SubString(Max(forwardSlashes.Last(), backSlashes.Last()));
		}
		else
		{
			name = name.SubString(forwardSlashes.Last());
		}
	}

	auto dots = name.OccurencesOf(".");
	if (!dots.IsEmpty())
	{
		return name.SubString(0, dots.Last());
	}

	return name;
}

Pair<String, String> String::ParseEquality(const String& equality)
{
	String key;
	String value;

	// Remove equal signs from equality
	auto occurences = equality.OccurencesOf("=");
	if (!occurences.IsEmpty())
	{
		key = equality.SubString(0, occurences.First());
		key = String::RemovePadding(key);
		value = equality.SubString(occurences.Last() + 1, equality.Length());
		value = String::RemovePadding(value);
	}

	return Pair<String, String>(key, value);
}

String String::RemovePadding(const String& string)
{
	uint32 start = 0;
	while (string._value[start] == ' ')
	{
		++start;
	}

	uint32 end = string.Length() - 1;
	while (string._value[end] == ' ')
	{
		--end;
	}

	return string.SubString(start, end + 1);
}

uint32 String::Length(const char* string)
{
	return (uint32)strlen(string);
}

int32 String::Compare(const char* stringA, const char* stringB, bool caseSensitive)
{
	if (caseSensitive)
	{
		return strcmp(stringA, stringB);
	}
	else
	{
		return _strcmpi(stringA, stringB);
	}
}

char String::ToChar(const String& string)
{
	return (char)std::stoi(string.Cstr());
}

int16 String::ToInt16(const String& string)
{
	return (int16)std::stoi(string.Cstr());
}

int32 String::ToInt32(const String& string)
{
	return std::stoi(string.Cstr());
}

int64 String::ToInt64(const String& string)
{
	return std::stol(string.Cstr());
}

byte String::ToByte(const String& string)
{
	return (byte)std::stoul(string.Cstr());
}

static uint16 ToUInt16(const String& string)
{
	return (uint16)std::stoul(string.Cstr());
}

static uint32 ToUint32(const String& string)
{
	return (uint32)std::stoul(string.Cstr());
}

static float ToFloat(const String& string)
{
	return std::stof(string.Cstr());
}

static double ToDouble(const String& string)
{
	return std::stod(string.Cstr());
}

static bool ToBool(const String& string)
{
	String value = string.ToLower();
	if (value == "true" || value == "1")
	{
		return true;
	}
	else
	{
		return false;
	}
}

/////////////////////
///   Operators   ///

String& String::operator=(const String& rhs)
{
	delete[] _value;
	this->_value = new char[rhs.Length() + 1];
	strcpy(_value, rhs._value);
	return This;
}

String& String::operator=(String&& other)
{
	if (this != &other)
	{
		delete[] _value;
		this->_value = other._value;
		other._value = nullptr;
	}
	return This;
}

bool Willow::operator==(const String& lhs, const String& rhs)
{
	return String::Compare(lhs._value, rhs._value) == 0;
}

bool Willow::operator!=(const String& lhs, const String& rhs)
{
	return String::Compare(lhs._value, rhs._value) != 0;
}

bool Willow::operator>(const String& lhs, const String& rhs)
{
	return String::Compare(lhs._value, rhs._value) > 0;
}

bool Willow::operator>=(const String& lhs, const String& rhs)
{
	return lhs > rhs || lhs == rhs;
}

bool Willow::operator<(const String& lhs, const String& rhs)
{
	return String::Compare(lhs._value, rhs._value) < 0;
}

bool Willow::operator<=(const String& lhs, const String& rhs)
{
	return lhs < rhs || lhs == rhs;
}

String Willow::operator+(const String& lhs, const String& rhs)
{
	char* string = new char[lhs.Length() + rhs.Length() + 1];
	strcpy(string, lhs._value);
	strcat(string, rhs._value);
	return string;
}

String& Willow::operator+=(String& lhs, const String& rhs)
{
	lhs = lhs + rhs;
	return lhs;
}