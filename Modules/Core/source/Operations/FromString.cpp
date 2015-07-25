// FromString.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <string>
#include "../../include/Core/Operations/FromString.h"

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	///////////////////////////
	///   Primitive Types   ///

	template <typename IntType>
	FORCEINLINE String IntFromString(const String& string, IntType& value)
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

	String FromString<bool>::Function(const String& string, bool& value)
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

	String FromString<char>::Function(const String& string, char& value)
	{
		value = string[1];
		return string.SubString(1);
	}

	String FromString<byte>::Function(const String& string, byte& value)
	{
		return IntFromString(string, value);
	}

	String FromString<int16>::Function(const String& string, int16& value)
	{
		return IntFromString(string, value);
	}

	String FromString<int32>::Function(const String& string, int32& value)
	{
		return IntFromString(string, value);
	}

	String FromString<int64>::Function(const String& string, int64& value)
	{
		return IntFromString(string, value);
	}

	String FromString<uint16>::Function(const String& string, uint16& value)
	{
		return IntFromString(string, value);
	}

	String FromString<uint32>::Function(const String& string, uint32& value)
	{
		return IntFromString(string, value);
	}

	String FromString<uint64>::Function(const String& string, uint64& value)
	{
		return IntFromString(string, value);
	}

	String FromString<float>::Function(const String& string, float& value)
	{
		size_t remainder;
		value = std::stof(string.Cstr(), &remainder);
		return string.SubString(static_cast<uint32>(remainder));
	}

	String FromString<double>::Function(const String& string, double& value)
	{
		size_t remainder;
		value = std::stod(string.Cstr(), &remainder);
		return string.SubString(static_cast<uint32>(remainder));
	}

	////////////////////////
	///   String Types   ///

	String FromString<String>::Function(const String& string, String& value)
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
