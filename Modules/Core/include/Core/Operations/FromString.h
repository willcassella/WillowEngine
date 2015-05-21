// FromString.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Reflection/TypeInfo.h"

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	///////////////////////////
	///   Primitive Types   ///

	/** Parse a bool from a String */
	template <>
	struct CORE_API FromString < bool >
	{
		static String Function(bool& value, const String& string);
	};

	/** Parse a character from a String */
	template <>
	struct CORE_API FromString < char >
	{
		static String Function(char& value, const String& string);
	};

	/** Parse a byte from a String */
	template <>
	struct CORE_API FromString < byte >
	{
		static String Function(byte& value, const String& string);
	};

	/** Parse a 16-bit integer from a String */
	template <>
	struct CORE_API FromString < int16 >
	{
		static String Function(int16& value, const String& string);
	};

	/** Parse a 32-bit integer from a String */
	template <>
	struct CORE_API FromString < int32 >
	{
		static String Function(int32& value, const String& string);
	};

	/** Parse a 64-bit integer from a String */
	template <>
	struct CORE_API FromString < int64 >
	{
		static String Function(int64& value, const String& string);
	};

	/** Parse an unsigned 16-bit integer from a String */
	template <>
	struct CORE_API FromString < uint16 >
	{
		static String Function(uint16& value, const String& string);
	};

	/** Parse an unsigned 32-bit integer from a String */
	template <>
	struct CORE_API FromString < uint32 >
	{
		static String Function(uint32& value, const String& string);
	};

	/** Parse an unsigned 64-bit integer from a String */
	template <>
	struct CORE_API FromString < uint64 >
	{
		static String Function(uint64& value, const String& string);
	};

	/** Parse a float from a String */
	template <>
	struct CORE_API FromString < float >
	{
		static String Function(float& value, const String& string);
	};

	/** Parse a double from a String */
	template <>
	struct CORE_API FromString < double >
	{
		static String Function(double& value, const String& string);
	};

	/** Parse a pointer from a String */
	template <typename AnyType>
	struct FromString < AnyType* >
	{
		static String Function(const AnyType*& value, const String& string)
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
	struct CORE_API FromString < String >
	{
		static String Function(String& value, const String& string);
	};
}