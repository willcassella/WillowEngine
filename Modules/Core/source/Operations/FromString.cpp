// FromString.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <string>
#include "../../include/Core/Operations/FromString.h"

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	///////////////////////////
	///   Primitive Types   ///

	template <typename IntT>
	FORCEINLINE String IntFromString(IntT& value, const String& string)
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

	String FromString<char>::Function(char& value, const String& string)
	{
		value = string[1];
		return string.SubString(1);
	}

	String FromString<byte>::Function(byte& value, const String& string)
	{
		return IntFromString(value, string);
	}

	String FromString<int16>::Function(int16& value, const String& string)
	{
		return IntFromString(value, string);
	}

	String FromString<int32>::Function(int32& value, const String& string)
	{
		return IntFromString(value, string);
	}

	String FromString<int64>::Function(int64& value, const String& string)
	{
		return IntFromString(value, string);
	}

	String FromString<uint16>::Function(uint16& value, const String& string)
	{
		return IntFromString(value, string);
	}

	String FromString<uint32>::Function(uint32& value, const String& string)
	{
		return IntFromString(value, string);
	}

	String FromString<uint64>::Function(uint64& value, const String& string)
	{
		return IntFromString(value, string);
	}

	String FromString<float>::Function(float& value, const String& string)
	{
		size_t remainder;
		value = std::stof(string.Cstr(), &remainder);
		return string.SubString(static_cast<uint32>(remainder));
	}

	String FromString<double>::Function(double& value, const String& string)
	{
		size_t remainder;
		value = std::stod(string.Cstr(), &remainder);
		return string.SubString(static_cast<uint32>(remainder));
	}

	String FromString<long double>::Function(long double& value, const String& string)
	{
		size_t remainder;
		value = std::stold(string.Cstr(), &remainder);
		return string.SubString(static_cast<uint32>(remainder));
	}

	////////////////////////
	///   String Types   ///

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
