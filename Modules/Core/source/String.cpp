// String.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <cstring>
#include <string>
#include "../include/Core/String.h"

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
	Array<char> result(Length());

	for (uint32 i = 0; i < Length(); ++i)
	{
		char character = This[i];

		switch (character)
		{
		case 'a':
			result.Add('A');
			break;
		case 'b':
			result.Add('B');
			break;
		case 'c':
			result.Add('C');
			break;
		case 'd':
			result.Add('D');
			break;
		case 'e':
			result.Add('E');
			break;
		case 'f':
			result.Add('F');
			break;
		case 'g':
			result.Add('G');
			break;
		case 'h':
			result.Add('H');
			break;
		case 'i':
			result.Add('I');
			break;
		case 'j':
			result.Add('J');
			break;
		case 'k':
			result.Add('K');
			break;
		case 'l':
			result.Add('L');
			break;
		case 'm':
			result.Add('M');
			break;
		case 'n':
			result.Add('N');
			break;
		case 'o':
			result.Add('O');
			break;
		case 'p':
			result.Add('P');
			break;
		case 'q':
			result.Add('Q');
			break;
		case 'r':
			result.Add('R');
			break;
		case 's':
			result.Add('S');
			break;
		case 't':
			result.Add('T');
			break;
		case 'u':
			result.Add('U');
			break;
		case 'v':
			result.Add('V');
			break;
		case 'w':
			result.Add('W');
			break;
		case 'x':
			result.Add('X');
			break;
		case 'y':
			result.Add('Y');
			break;
		case 'z':
			result.Add('Z');
			break;
		default:
			result.Add(character);
			break;
		}
	}

	return String(result);
}

String String::ToLower() const
{
	Array<char> result(Length());

	for (uint32 i = 0; i < Length(); ++i)
	{
		char character = This[i];

		switch (character)
		{
		case 'A':
			result.Add('a');
			break;
		case 'B':
			result.Add('b');
			break;
		case 'C':
			result.Add('c');
			break;
		case 'D':
			result.Add('d');
			break;
		case 'E':
			result.Add('e');
			break;
		case 'F':
			result.Add('f');
			break;
		case 'G':
			result.Add('g');
			break;
		case 'H':
			result.Add('h');
			break;
		case 'I':
			result.Add('i');
			break;
		case 'J':
			result.Add('j');
			break;
		case 'K':
			result.Add('k');
			break;
		case 'L':
			result.Add('l');
			break;
		case 'M':
			result.Add('m');
			break;
		case 'N':
			result.Add('n');
			break;
		case 'O':
			result.Add('o');
			break;
		case 'P':
			result.Add('p');
			break;
		case 'Q':
			result.Add('q');
			break;
		case 'R':
			result.Add('r');
			break;
		case 'S':
			result.Add('s');
			break;
		case 'T':
			result.Add('t');
			break;
		case 'U':
			result.Add('u');
			break;
		case 'V':
			result.Add('v');
			break;
		case 'W':
			result.Add('w');
			break;
		case 'X':
			result.Add('x');
			break;
		case 'Y':
			result.Add('y');
			break;
		case 'Z':
			result.Add('z');
			break;
		default:
			result.Add(character);
			break;
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
	else if (!backSlashes.IsEmpty())
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

namespace Implementation
{
	template <typename IntType>
	FORCEINLINE String IntToString(IntType value)
	{
		String result;

		if (value < 0)
		{
			result = '-';
			value *= -1;
		}

		if (value == 0)
		{
			return '0';
		}

		while (value != 0)
		{
			IntType digit = value % 10;

			switch (digit)
			{
			case 0:
				result += '0';
				break;
			case 1:
				result += '1';
				break;
			case 2:
				result += '2';
				break;
			case 3:
				result += '3';
				break;
			case 4:
				result += '4';
				break;
			case 5:
				result += '5';
				break;
			case 6:
				result += '6';
				break;
			case 7:
				result += '7';
				break;
			case 8:
				result += '8';
				break;
			case 9:
				result += '9';
			}

			value /= 10;
		}

		return result.Reverse();
	}

	template <typename IntType>
	FORCEINLINE String IntFromString(IntType& value, const String& string)
	{
		value = 0;

		for (uint32 i = 0; i < string.Length(); ++i)
		{
			switch (string[i])
			{
			case '0':
				value *= 10;
				break;
			case '1':
				value *= 10;
				value += 1;
				break;
			case '2':
				value *= 10;
				value += 2;
				break;
			case '3':
				value *= 10;
				value += 3;
				break;
			case '4':
				value *= 10;
				value += 4;
				break;
			case '5':
				value *= 10;
				value += 5;
				break;
			case '6':
				value *= 10;
				value += 6;
				break;
			case '7':
				value *= 10;
				value += 7;
				break;
			case '8':
				value *= 10;
				value += 8;
				break;
			case '9':
				value *= 10;
				value += 9;
				break;
			default:
				return string.SubString(i);
			}
		}

		return "";
	}

	String ToString<bool>::Function(bool value)
	{
		if (value)
		{
			return String("true");
		}
		else
		{
			return String("false");
		}
	}

	String FromString<bool>::Function(bool& value, const String& string)
	{
		String head = string.SubString(0, 6).ToLower();

		if (head.StartsWith("true"))
		{
			value = true;
			return string.SubString(4);
		}
		else if (head.StartsWith("false"))
		{
			value = false;
			return string.SubString(5);
		}
		else
		{
			return string;
		}
	}

	String ToString<char>::Function(char value)
	{
		return String(value);
	}

	String FromString<char>::Function(char& value, const String& string)
	{
		value = string[1];
		return string.SubString(1);
	}

	String ToString<byte>::Function(byte value)
	{
		return IntToString(value);
	}

	String FromString<byte>::Function(byte& value, const String& string)
	{
		return IntFromString(value, string);
	}

	String ToString<int16>::Function(int16 value)
	{
		return IntToString(value);
	}

	String FromString<int16>::Function(int16& value, const String& string)
	{
		return IntFromString(value, string);
	}

	String ToString<int32>::Function(int32 value)
	{
		return IntToString(value);
	}

	String FromString<int32>::Function(int32& value, const String& string)
	{
		return IntFromString(value, string);
	}

	String ToString<int64>::Function(int64 value)
	{
		return IntToString(value);
	}

	String FromString<int64>::Function(int64& value, const String& string)
	{
		return IntFromString(value, string);
	}

	String ToString<uint16>::Function(uint16 value)
	{
		return IntToString(value);
	}

	String FromString<uint16>::Function(uint16& value, const String& string)
	{
		return IntFromString(value, string);
	}

	String ToString<uint32>::Function(uint32 value)
	{
		return IntToString(value);
	}

	String FromString<uint32>::Function(uint32& value, const String& string)
	{
		return IntFromString(value, string);
	}

	String ToString<uint64>::Function(uint64 value)
	{
		return IntToString(value);
	}

	String FromString<uint64>::Function(uint64& value, const String& string)
	{
		return IntFromString(value, string);
	}

	String ToString<float>::Function(float value)
	{
		return String(std::to_string(value).c_str());
	}

	String FromString<float>::Function(float& value, const String& string)
	{
		size_t remainder;
		value = std::stof(string.Cstr(), &remainder);
		return string.SubString(static_cast<uint32>(remainder));
	}

	String ToString<double>::Function(double value)
	{
		return String(std::to_string(value).c_str());
	}

	String FromString<double>::Function(double& value, const String& string)
	{
		size_t remainder;
		value = std::stod(string.Cstr(), &remainder);
		return string.SubString(static_cast<uint32>(remainder));
	}

	String FromString<String>::Function(String& value, const String& string)
	{
		if (string.StartsWith('"'))
		{
			for (uint32 i = 1; i < string.Length(); ++i)
			{
				if (string[i] == '"')
				{
					return string.SubString(i + 1);
				}
				else
				{
					value += string[i];
				}
			}

			// We've reached the end of the String
			return "";
		}
		else
		{
			value = "";
			return string;
		}
	}
}