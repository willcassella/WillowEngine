// FromString.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../String.h"

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Default implementation of 'FromString', defined in 'Reflection/TypeInfo.h' */
	template <typename T>
	struct FromString;

	///////////////////////////
	///   Primitive Types   ///

	/** Parse a bool from a String */
	template <>
	struct CORE_API FromString < bool > final
	{
		static String Function(const String& string, bool& value);
	};

	/** Parse a character from a String */
	template <>
	struct CORE_API FromString < char > final
	{
		static String Function(const String& string, char& value);
	};

	/** Parse a byte from a String */
	template <>
	struct CORE_API FromString < byte > final
	{
		static String Function(const String& string, byte& value);
	};

	/** Parse a 16-bit integer from a String */
	template <>
	struct CORE_API FromString < int16 > final
	{
		static String Function(const String& string, int16& value);
	};

	/** Parse a 32-bit integer from a String */
	template <>
	struct CORE_API FromString < int32 > final
	{
		static String Function(const String& string, int32& value);
	};

	/** Parse a 64-bit integer from a String */
	template <>
	struct CORE_API FromString < int64 > final
	{
		static String Function(const String& string, int64& value);
	};

	/** Parse an unsigned 16-bit integer from a String */
	template <>
	struct CORE_API FromString < uint16 > final
	{
		static String Function(const String& string, uint16& value);
	};

	/** Parse an unsigned 32-bit integer from a String */
	template <>
	struct CORE_API FromString < uint32 > final
	{
		static String Function(const String& string, uint32& value);
	};

	/** Parse an unsigned 64-bit integer from a String */
	template <>
	struct CORE_API FromString < uint64 > final
	{
		static String Function(const String& string, uint64& value);
	};

	/** Parse a float from a String */
	template <>
	struct CORE_API FromString < float > final
	{
		static String Function(const String& string, float& value);
	};

	/** Parse a double from a String */
	template <>
	struct CORE_API FromString < double > final
	{
		static String Function(const String& string, double& value);
	};

	/** Parse a pointer from a String */
	template <typename AnyType>
	struct FromString < AnyType* > final
	{
		static String Function(const String& string, AnyType*& value)
		{
			if (string.StartsWith("0x"))
			{
				value = nullptr;
				return string.SubString(9); // @TODO: Implement this
			}
			else
			{
				value = nullptr;
				return string;
			}
		}
	};

	////////////////////////
	///   String Types   ///

	/** Parse a String from a String */
	template <>
	struct CORE_API FromString < String > final
	{
		static String Function(const String& string, String& value);
	};
}

/////////////////////
///   Functions   ///

/** Parses the given value from the given String, following the given format. The remainder of the String is returned.
* - The location of the '@' character in the format String denotes the location of the value in the given String */
template <typename T>
static String FromString(const String& string, const String& format, T& value)
{
	for (uint32 i = 0; i < format.Length(); ++i)
	{
		if (format[i] == '@')
		{
			return FromString(string.SubString(i), value);
		}
	}

	// You passed in an empty format String, dumbass
	return "";
}

/** Parses the given values from the given String, following the given format. The remainder of the String is returned.
* - Each location of the '@' character in the format String denotes the location of the respective value in the given String */
template <typename T, typename ... MoreT>
static String FromString(const String& string, const String& format, T& value, MoreT& ... moreValues)
{
	for (uint32 i = 0; i < format.Length(); ++i)
	{
		if (format[i] == '@')
		{
			return FromString(FromString(string.SubString(i), value), format.SubString(i + 1), moreValues...);
		}
	}

	// You passed in an empty format String, dumbass
	return "";
}
