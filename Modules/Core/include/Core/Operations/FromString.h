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
		static String Function(bool& value, const String& string);
	};

	/** Parse a character from a String */
	template <>
	struct CORE_API FromString < char > final
	{
		static String Function(char& value, const String& string);
	};

	/** Parse a byte from a String */
	template <>
	struct CORE_API FromString < byte > final
	{
		static String Function(byte& value, const String& string);
	};

	/** Parse a 16-bit integer from a String */
	template <>
	struct CORE_API FromString < int16 > final
	{
		static String Function(int16& value, const String& string);
	};

	/** Parse a 32-bit integer from a String */
	template <>
	struct CORE_API FromString < int32 > final
	{
		static String Function(int32& value, const String& string);
	};

	/** Parse a 64-bit integer from a String */
	template <>
	struct CORE_API FromString < int64 > final
	{
		static String Function(int64& value, const String& string);
	};

	/** Parse an unsigned 16-bit integer from a String */
	template <>
	struct CORE_API FromString < uint16 > final
	{
		static String Function(uint16& value, const String& string);
	};

	/** Parse an unsigned 32-bit integer from a String */
	template <>
	struct CORE_API FromString < uint32 > final
	{
		static String Function(uint32& value, const String& string);
	};

	/** Parse an unsigned 64-bit integer from a String */
	template <>
	struct CORE_API FromString < uint64 > final
	{
		static String Function(uint64& value, const String& string);
	};

	/** Parse a float from a String */
	template <>
	struct CORE_API FromString < float > final
	{
		static String Function(float& value, const String& string);
	};

	/** Parse a double from a String */
	template <>
	struct CORE_API FromString < double > final
	{
		static String Function(double& value, const String& string);
	};

	/** Parse a pointer from a String */
	template <typename AnyType>
	struct FromString < AnyType* > final
	{
		static String Function(AnyType*& value, const String& string)
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
		static String Function(String& value, const String& string);
	};
}