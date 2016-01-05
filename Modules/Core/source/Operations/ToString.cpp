// ToString.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <string>
#include "../../include/Core/Operations/ToString.h"

//////////////////////////
///   Implementation   ///

namespace Implementation
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

	String ToString<char>::Function(char value)
	{
		return String(value);
	}

	String ToString<byte>::Function(byte value)
	{
		return IntToString(value);
	}

	String ToString<int16>::Function(int16 value)
	{
		return IntToString(value);
	}

	String ToString<int32>::Function(int32 value)
	{
		return IntToString(value);
	}

	String ToString<int64>::Function(int64 value)
	{
		return IntToString(value);
	}

	String ToString<uint16>::Function(uint16 value)
	{
		return IntToString(value);
	}

	String ToString<uint32>::Function(uint32 value)
	{
		return IntToString(value);
	}

	String ToString<uint64>::Function(uint64 value)
	{
		return IntToString(value);
	}

	String ToString<float>::Function(float value)
	{
		return String(std::to_string(value).c_str());
	}

	String ToString<double>::Function(double value)
	{
		return String(std::to_string(value).c_str());
	}

	String ToString<long double>::Function(long double value)
	{
		return String(std::to_string(value).c_str());
	}
}