// string.cpp

#include "..\include\Utility\String.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

String::String(const char* _value)
{
	value = _value;
}

/////////////////////
///   Operators   ///

String& String::operator=(const char* rhs)
{
	value = rhs;
	return *this;
}

String::operator const char*() const
{
	return value;
}