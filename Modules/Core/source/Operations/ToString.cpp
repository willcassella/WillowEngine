// ToString.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <string>
#include "../../include/Core/Operations/ToString.h"

namespace Operations
{
	///////////////////////////
	///   Primitive Types   ///

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

	void ToString<bool>::Function(String& out, bool value)
	{
		if (value)
		{
			out = "true";
		}
		else
		{
			out = "false";
		}
	}

	void ToString<char>::Function(String& out, char value)
	{
		out = value;
	}

	void ToString<byte>::Function(String& out, byte value)
	{
		out = IntToString(value);
	}

	void ToString<int16>::Function(String& out, int16 value)
	{
		out = IntToString(value);
	}

	void ToString<int32>::Function(String& out, int32 value)
	{
		out = IntToString(value);
	}

	void ToString<int64>::Function(String& out, int64 value)
	{
		out = IntToString(value);
	}

	void ToString<uint16>::Function(String& out, uint16 value)
	{
		out = IntToString(value);
	}

	void ToString<uint32>::Function(String& out, uint32 value)
	{
		out = IntToString(value);
	}

	void ToString<uint64>::Function(String& out, uint64 value)
	{
		out = IntToString(value);
	}

	void ToString<float>::Function(String& out, float value)
	{
		out = std::to_string(value).c_str();
	}

	void ToString<double>::Function(String& out, double value)
	{
		out = std::to_string(value).c_str();
	}

	void ToString<long double>::Function(String& out, long double value)
	{
		out = std::to_string(value).c_str();
	}
}