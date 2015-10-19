// String.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <cstring>
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
	Array<Char> result(Length());

	for (uint32 i = 0; i < Length(); ++i)
	{
		Char character = self[i];

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
	Array<Char> result(Length());

	for (uint32 i = 0; i < Length(); ++i)
	{
		Char character = self[i];

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
		if (self[i] != string[i])
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
		if (self[Length() - i] != string[string.Length() - i])
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
	Array<Char> result;

	for (int32 i = Length(); i > 0; --i)
	{
		result.Add(self[i - 1]);
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
		return Compare(stringA.ToLower(), stringB.ToLower(), true);
	}

	return strcmp(stringA.Cstr(), stringB.Cstr());
}

/////////////////////
///   Operators   ///

String& String::operator=(CString rhs)
{
	_value = Array<Char>(rhs, Length(rhs) + 1);
	return self;
}

String& String::operator=(Char rhs)
{
	_value.Reset(2);
	_value.Add(rhs);
	_value.Add('\0');
	return self;
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
