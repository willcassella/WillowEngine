// string.cpp

#include <cstring>
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

String String::GetFileExtension() const
{
	auto occurences = this->OccurencesOf(".");
	if (!occurences.IsEmpty())
	{
		return this->SubString(occurences.Last() + 1);
	}
	else
	{
		return "";
	}
}

String String::GetFileName() const
{
	String name = This;

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