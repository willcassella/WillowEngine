// FromString.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <string>
#include "../../include/Core/Operations/FromString.h"

namespace Operations
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

	void FromString<bool>::Function(String& out, bool& value, const String& string)
	{
		String head = string.SubString(0, 6).ToLower();

		if (head.StartsWith("true"))
		{
			value = true;
			out = string.SubString(4);
		}
		else if (head.StartsWith("false"))
		{
			value = false;
			out = string.SubString(5);
		}
		else
		{
			out = string;
		}
	}

	void FromString<char>::Function(String& out, char& value, const String& string)
	{
		value = string[1];
		out = string.SubString(1);
	}

	void FromString<byte>::Function(String& out, byte& value, const String& string)
	{
		out = IntFromString(value, string);
	}

	void FromString<int16>::Function(String& out, int16& value, const String& string)
	{
		out = IntFromString(value, string);
	}

	void FromString<int32>::Function(String&out, int32& value, const String& string)
	{
		out = IntFromString(value, string);
	}

	void FromString<int64>::Function(String& out, int64& value, const String& string)
	{
		out = IntFromString(value, string);
	}

	void FromString<uint16>::Function(String& out, uint16& value, const String& string)
	{
		out = IntFromString(value, string);
	}

	void FromString<uint32>::Function(String& out, uint32& value, const String& string)
	{
		out = IntFromString(value, string);
	}

	void FromString<uint64>::Function(String& out, uint64& value, const String& string)
	{
		out = IntFromString(value, string);
	}

	void FromString<float>::Function(String& out, float& value, const String& string)
	{
		size_t remainder;
		value = std::stof(string.Cstr(), &remainder);
		out = string.SubString(static_cast<uint32>(remainder));
	}

	void FromString<double>::Function(String& out, double& value, const String& string)
	{
		size_t remainder;
		value = std::stod(string.Cstr(), &remainder);
		out = string.SubString(static_cast<uint32>(remainder));
	}

	void FromString<long double>::Function(String& out, long double& value, const String& string)
	{
		size_t remainder;
		value = std::stold(string.Cstr(), &remainder);
		out = string.SubString(static_cast<uint32>(remainder));
	}

	////////////////////////
	///   String Types   ///

	void FromString<String>::Function(String& out, String& value, const String& string)
	{
		if (string.StartsWith('"'))
		{
			for (uint32 i = 1; i < string.Length(); ++i)
			{
				if (string[i] == '"')
				{
					out = string.SubString(i + 1);
					return;
				}
				else
				{
					value += string[i];
				}
			}

			// We've reached the end of the String
			out = "";
		}
		else
		{
			value = "";
			out = string;
		}
	}
}
