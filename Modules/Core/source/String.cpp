// String.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <cstring>
#include <string>
#include "../include/Core/String.h"

////////////////
///   Data   ///

// @TODO: Do something else with this?
const Table<char, char> LowerToUpper = {
	{ 'a', 'A' },
	{ 'b', 'B' },
	{ 'c', 'C' },
	{ 'd', 'D' },
	{ 'e', 'E' },
	{ 'f', 'F' },
	{ 'g', 'G' },
	{ 'h', 'H' },
	{ 'i', 'I' },
	{ 'j', 'J' },
	{ 'k', 'K' },
	{ 'l', 'L' },
	{ 'm', 'M' },
	{ 'n', 'N' },
	{ 'o', 'O' },
	{ 'p', 'P' },
	{ 'q', 'Q' },
	{ 'r', 'R' },
	{ 's', 'S' },
	{ 't', 'T' },
	{ 'u', 'U' },
	{ 'v', 'V' },
	{ 'w', 'W' },
	{ 'x', 'X' },
	{ 'y', 'Y' },
	{ 'z', 'Z' }
};

const Table <char, char> UpperToLower = {
	{ 'A', 'a' },
	{ 'B', 'b' },
	{ 'C', 'c' },
	{ 'D', 'd' },
	{ 'E', 'e' },
	{ 'F', 'f' },
	{ 'G', 'g' },
	{ 'H', 'h' },
	{ 'I', 'i' },
	{ 'J', 'j' },
	{ 'K', 'k' },
	{ 'L', 'l' },
	{ 'M', 'm' },
	{ 'N', 'n' },
	{ 'O', 'o' },
	{ 'P', 'p' },
	{ 'Q', 'q' },
	{ 'R', 'r' },
	{ 'S', 's' },
	{ 'T', 't' },
	{ 'U', 'u' },
	{ 'V', 'v' },
	{ 'W', 'w' },
	{ 'X', 'x' },
	{ 'Y', 'y' },
	{ 'Z', 'z' }
};

///////////////////
///   Methods   ///

String String::SubString(uint32 start, uint32 end) const
{
	if (start >= end || start >= Length())
	{
		return "";
	}

	return _value.Slice(start, end);
}

String String::ToUpper() const
{
	Array<char> result;

	for (uint32 i = 0; i < Length(); ++i)
	{
		const char* character = LowerToUpper.Find(This[i]);

		// If the character is already uppercase or not an uppercase-able character
		if (character == nullptr)
		{
			result.Add(This[i]);
		}
		else
		{
			result.Add(*character);
		}
	}

	return String(result);
}

String String::ToLower() const
{
	Array<char> result;

	for (uint32 i = 0; i < Length(); ++i)
	{
		const char* character = UpperToLower.Find(This[i]);

		// If the character is already lowercase or not a lowercase-able character
		if (character == nullptr)
		{
			result.Add(This[i]);
		}
		else
		{
			result.Add(*character);
		}
	}

	return String(result);
}

bool String::StartsWith(const String& string) const
{
	for (uint32 i = 0; i < string.Length(); ++i)
	{
		if (This[i] != string[i])
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
		if (This[Length() - i] != string[string.Length() - i])
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

	for (uint32 i = 0; i < Length(); ++i)
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
	Array<char> result;

	for (int32 i = Length(); i > 0; --i)
	{
		result.Add(This[i - 1]);
	}

	return String(result);
}

String String::GetFileExtension(const String& path)
{
	auto occurences = path.OccurencesOf('.');
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
			if (forwardSlashes.Last() >= backSlashes.Last())
			{
				name = name.SubString(forwardSlashes.Last());
			}
			else
			{
				name = name.SubString(backSlashes.Last());
			}
		}
		else
		{
			name = name.SubString(forwardSlashes.Last());
		}
	}
	else
	{
		name = name.SubString(backSlashes.Last());
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

String& String::operator=(const char* rhs)
{
	_value = Array<char>(rhs, String::Length(rhs) + 1);
	return This;
}

String& String::operator=(char rhs)
{
	_value.Reset(2);
	_value.Add(rhs);
	_value.Add('\0');
	return This;
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
	Array<char> result = lhs._value.Slice(0, lhs.Length()) + rhs._value.Slice(0, rhs.Length());
	return String(result);
}

//////////////////////////
///   Implementation   ///

String Implementation::FloatToString(float value)
{
	return String(std::to_string(value).c_str());
}

String Implementation::FloatFromString(float& value, const String& string)
{
	size_t remainder;
	value = std::stof(string.Cstr(), &remainder);
	return "Not finished";
}

String Implementation::DoubleToString(double value)
{
	return String(std::to_string(value).c_str());
}

String Implementation::DoubleFromString(double& value, const String& string)
{
	size_t remainder;
	value = std::stod(string.Cstr(), &remainder);
	return "Not finished";
}