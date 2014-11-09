// string.cpp

#include <cstring>
#include <string>
#include <ctype.h>
#include "..\include\Utility\Math\Math.h"
#include "..\include\Utility\Reflection\Reflection.h"
using namespace Willow;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(Willow::String)
HAS_FACTORY
END_REFLECTION_INFO

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

const char* String::Cstr(uint32 startIndex) const
{
	if (startIndex < this->Length())
	{
		return &_value[startIndex];
	}
	else
	{
		return "";
	}
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
	for (uint32 i = 0; i < end - start; ++i)
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

	for (uint32 i = 0; i < str.Length(); ++i)
	{
		str._value[i] = toupper(str._value[i]);
	}

	return str;
}

String String::ToLower() const
{
	String str = This;

	for (uint32 i = 0; i < str.Length(); ++i)
	{
		str._value[i] = tolower(str._value[i]);
	}

	return str;
}

bool String::StartsWith(const String& string) const
{
	for (uint32 index = 0; index < string.Length(); ++index)
	{
		if (This[index] != string[index])
		{
			return false;
		}
	}

	return true;
}

bool String::EndsWith(const String& string) const
{
	for (uint32 index = 0; index < string.Length(); ++index)
	{
		if (This[this->Length() - index] != string[string.Length() - index])
		{
			return false;
		}
	}

	return true;
}

List<uint32> String::OccurencesOf(const String& string) const
{
	List<uint32> occurences;

	for (uint32 i = 0; i < this->Length(); ++i)
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

Pair<String, String> String::ParseNamespace(const String& fullName)
{
	auto colons = fullName.OccurencesOf("::");

	if (!colons.IsEmpty())
	{
		uint32 last = colons.Last();
		return Pair<String, String>(fullName.SubString(0, last), fullName.SubString(last + 2));
	}
	else
	{
		return Pair<String, String>("", fullName);
	}
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

char String::operator[](uint32 index) const
{
	if (index < this->Length())
	{
		return _value[index];
	}
	else
	{
		return '\0';
	}
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

/////////////////////////
///   ValueToString   ///

String Willow::ValueToString(const object& value)
{
	return value.ToString();
}

String Willow::ValueToString(const Interface& value)
{
	return ((const object&)value).ToString();
}

String Willow::ValueToString(const char* value)
{
	return value;
}

String Willow::ValueToString(const void* value)
{
	return ValueToString((uint64)value);
}

String Willow::ValueToString(bool value)
{
	if (value)
	{
		return "true";
	}
	else
	{
		return "false";
	}
}

String Willow::ValueToString(char value)
{
	char str[2];
	str[0] = value;
	str[1] = '\0';
	return str;
}

String Willow::ValueToString(byte value)
{
	return std::to_string(value).c_str();
}

String Willow::ValueToString(int16 value)
{
	return std::to_string(value).c_str();
}

String Willow::ValueToString(int32 value)
{
	return std::to_string(value).c_str();
}

String Willow::ValueToString(int64 value)
{
	return std::to_string(value).c_str();
}

String Willow::ValueToString(ubyte value)
{
	return std::to_string(value).c_str();
}

String Willow::ValueToString(uint16 value)
{
	return std::to_string(value).c_str();
}

String Willow::ValueToString(uint32 value)
{
	return std::to_string(value).c_str();
}

String Willow::ValueToString(uint64 value)
{
	return std::to_string(value).c_str();
}

String Willow::ValueToString(float value)
{
	return std::to_string(value).c_str();
}

String Willow::ValueToString(double value)
{
	return std::to_string(value).c_str();
}

///////////////////////////
///   ValueFromString   ///

String Willow::ValueFromString(const String& string, const void*& outValue)
{
	return ValueFromString(string, (uint64&)outValue);
}

String Willow::ValueFromString(const String& string, bool& outValue)
{
	String value = string.ToLower();
	if (value.StartsWith("true"))
	{
		outValue = true;
		return string.Cstr(4);
	}
	else if (value.StartsWith("1"))
	{
		outValue = true;
		return string.Cstr(1);
	}
	else
	{
		outValue = false;
		return string;
	}
}

String Willow::ValueFromString(const String& string, char& outValue)
{
	size_t index;
	outValue = (char)std::stoi(string.Cstr(), &index);
	return &string.Cstr()[index];
}

String Willow::ValueFromString(const String& string, byte& outValue)
{
	size_t index;
	outValue = (byte)std::stoi(string.Cstr(), &index);
	return &string.Cstr()[index];
}

String Willow::ValueFromString(const String& string, int16& outValue)
{
	size_t index;
	outValue = (int16)std::stoi(string.Cstr(), &index);
	return &string.Cstr()[index];
}

String Willow::ValueFromString(const String& string, int32& outValue)
{
	size_t index;
	outValue = std::stoi(string.Cstr(), &index);
	return &string.Cstr()[index];
}

String Willow::ValueFromString(const String& string, int64& outValue)
{
	size_t index;
	outValue = std::stol(string.Cstr(), &index);
	return &string.Cstr()[index];
}

String Willow::ValueFromString(const String& string, ubyte& outValue)
{
	size_t index;
	outValue = (ubyte)std::stoul(string.Cstr(), &index);
	return &string.Cstr()[index];
}

String Willow::ValueFromString(const String& string, uint16& outValue)
{
	size_t index;
	outValue = (uint16)std::stoul(string.Cstr(), &index);
	return &string.Cstr()[index];
}

String Willow::ValueFromString(const String& string, uint32& outValue)
{
	size_t index;
	outValue = (uint32)std::stoul(string.Cstr(), &index);
	return &string.Cstr()[index];
}

String Willow::ValueFromString(const String& string, uint64& outValue)
{
	size_t index;
	outValue = (uint64)std::stoull(string.Cstr(), &index);
	return &string.Cstr()[index];
}

String Willow::ValueFromString(const String& string, float& outValue)
{
	size_t index;
	outValue = std::stof(string.Cstr(), &index);
	return &string.Cstr()[index];
}

String Willow::ValueFromString(const String& string, double& outValue)
{
	size_t index;
	outValue = std::stod(string.Cstr(), &index);
	return &string.Cstr()[index];
}