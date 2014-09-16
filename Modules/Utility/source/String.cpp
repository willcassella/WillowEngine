// string.cpp

#include <cstring>
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

size_t String::Length() const
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

Array<uint32> String::OccurencesOf(const String& string) const
{
	Array<uint32> occurences;

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
	return SubString(this->OccurencesOf(".").Last() + 1);
}

size_t String::Length(const char* string)
{
	return strlen(string);
}

/////////////////////
///   Operators   ///

String& String::operator=(const String& rhs)
{
	delete[] _value;
	this->_value = new char[rhs.Length()];
	strcpy(_value, rhs._value);
	return *this;
}

String& String::operator=(String&& other)
{
	if (this != &other)
	{
		delete[] _value;
		this->_value = other._value;
		other._value = nullptr;
	}
	return *this;
}

//String& String::operator=(const char* rhs)
//{
//	delete[] _value;
//	this->_value = new char[String::Length(rhs)];
//	strcpy(_value, rhs);
//	return *this;
//}

String& String::operator+=(const String& rhs)
{
	/*char* tempValue = new char[this->Length() + rhs.Length() + 1];
	strcpy(tempValue, _value);
	strcat(tempValue, rhs._value);
	delete[] _value;
	_value = tempValue;
	return *this;*/
	*this = *this + rhs;
	return *this;
}

//String& String::operator+=(const char* rhs)
//{
//	char* tempValue = new char[this->Length() + String::Length(rhs) + 1];
//	strcpy(tempValue, _value);
//	strcat(tempValue, rhs);
//	delete[] _value;
//	_value = tempValue;
//	return *this;
//}

bool Willow::operator==(const String& lhs, const String& rhs)
{
	return strcmp(lhs._value, rhs._value) == 0;
}

//bool Willow::operator==(const String& lhs, const char* rhs)
//{
//	return strcmp(lhs._value, rhs) == 0;
//}

//bool Willow::operator==(const char* lhs, const String& rhs)
//{
//	return strcmp(lhs, rhs._value) == 0;
//}

bool Willow::operator!=(const String& lhs, const String& rhs)
{
	return strcmp(lhs._value, rhs._value) != 0;
}

//bool Willow::operator!=(const String& lhs, const char* rhs)
//{
//	return strcmp(lhs._value, rhs) != 0;
//}

//bool Willow::operator!=(const char* lhs, const String& rhs)
//{
//	return strcmp(lhs, rhs._value) != 0;
//}

bool Willow::operator>(const String& lhs, const String& rhs)
{
	return strcmp(lhs._value, rhs._value) > 0;
}

//bool Willow::operator>(const String& lhs, const char* rhs)
//{
//	return strcmp(lhs._value, rhs) > 0;
//}

//bool Willow::operator>(const char* lhs, const String& rhs)
//{
//	return strcmp(lhs, rhs._value) > 0;
//}

bool Willow::operator<(const String& lhs, const String& rhs)
{
	return strcmp(lhs._value, rhs._value) < 0;
}

//bool Willow::operator<(const String& lhs, const char* rhs)
//{
//	return strcmp(lhs._value, rhs) < 0;
//}

//bool Willow::operator<(const char* lhs, const String& rhs)
//{
//	return strcmp(lhs, rhs._value) < 0;
//}

String Willow::operator+(const String& lhs, const String& rhs)
{
	char* string = new char[lhs.Length() + rhs.Length() + 1];
	strcpy(string, lhs._value);
	strcat(string, rhs._value);
	return string;
}

//String Willow::operator+(const String& lhs, const char* rhs)
//{
//	char* string = new char[lhs.Length() + String::Length(rhs) + 1];
//	strcpy(string, lhs._value);
//	strcat(string, rhs);
//	return string;
//}

//String Willow::operator+(const char* lhs, const String& rhs)
//{
//	char* string = new char[String::Length(lhs), rhs.Length() + 1];
//	strcpy(string, lhs);
//	strcat(string, rhs._value);
//	return string;
//}

std::ostream& Willow::operator<<(std::ostream& lhs, const String& rhs)
{
	lhs << rhs._value;
	return lhs;
}