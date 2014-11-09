// String.h
#pragma once

#include "Reflection\object.h"
#include "Reflection\Interface.h"

namespace Willow
{
	/** Forward declerations */
	template <typename T> class List;
	template <typename A, typename B> class Pair;
	template <typename T> struct __type_info__;

	class UTILITY_API String : public object
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(object)

		////////////////////////
		///   Constructors   ///
	public:

		/** Constructs a new String
		value - the c-style string to set this String to */
		String(const char* value = "");
		String(const String& copy);
		String(String&& other);
		~String();

		///////////////////
		///   Methods   ///
	public:

		inline String ToString() const override
		{
			return This;
		}

		/** Returns whether this string is empty */
		bool IsNullOrEmpty() const;

		/** Returns the number of characters in this string */
		uint32 Length() const;

		/** Converts this string to a c style string */
		const char* Cstr(uint32 startIndex = 0) const;

		/** Returns a substring from the character at the start index to the end of the string
		* Returns an empty string if start is greater than the length of the string */
		String SubString(uint32 start) const;
		
		/** Returns a substring from the character at the start index to the character and the end index
		* Returns an empty string if start is greater than end or start is greater than the length of the string */
		String SubString(uint32 start, uint32 end) const;

		/** Returns a copy of this string with all lower-case characters */
		String ToUpper() const;

		/** Returns a copy of this string with all upper-case characters */
		String ToLower() const;

		/** Returns whether this string begins with the given string */
		bool StartsWith(const String& string) const;

		/** Returns whether this string ends with the given string */
		bool EndsWith(const String& string) const;

		/** Returns a list of the starting indices at which the given string appears in this string */
		List<uint32> OccurencesOf(const String& string) const;
		
		/** If this string represents a path to a file, returns the file extension */
		static String GetFileExtension(const String& path);

		/** If this string represents a path to a file, returns the name of the file */
		static String GetFileName(const String& path);

		/** Parses a string in the form 'key = value'
		* Returns a pair consisting of the key and value
		* Returns an empty pair if the string could not be parsed*/
		static Pair<String, String> ParseEquality(const String& equality);
		
		/** Parses a string representing a full class name (like Willow::String)
		* Returns a pair consisting of the namespace and classname 
		* Can handle nested namespaces */
		static Pair<String, String> ParseNamespace(const String& fullName);

		/** Removes spaces from the front and end of string
		front : whether to remove padding from the front of the string (defaults to true) 
		back : whether to remove padding from the back of the string (defaults to true) */
		static String RemovePadding(const String& string, bool front = true, bool back = true);

		/** Returns the length of a c-style string */
		static uint32 Length(const char* string);

		/** Compares two c-style strings
		Return values:
		0 - stringA and stringB are equal
		<0 - stringA is alphabetically lower than stringB
		>0 - stringB is alphabetically higher than stringB */
		static int32 Compare(const char* stringA, const char* stringB, bool caseSensitive = true);

		/** Attempts to parse a string using the given format string
		* Returns the rest of the string */
		template <typename FirstType>
		static String ParseValues(const String& string, const String& format, FirstType& outValue)
		{
			using Willow::ValueFromString;

			// Iterate through the string
			for (uint32 i = 0; format[i] != '\0'; ++i)
			{
				if (format[i] == '@')
				{
					return ValueFromString(string.Cstr(i), outValue);
				}
			}

			// The format was not found
			return "";
		}

		/** Attempts to parse a string using the given format string
		* Returns the rest of the string */
		template <typename FirstType, typename ... ArgTypes>
		static String ParseValues(const String& string, const String& format, FirstType& outValue, ArgTypes& ... outValues)
		{
			using Willow::ValueFromString;

			// Iterate through the string
			for (uint32 i = 0; format[i] != '\0'; ++i)
			{
				if (format[i] == '@')
				{
					return String::ParseValues(ValueFromString(string.SubString(i), outValue), format.SubString(i + 1), outValues...);
				}
			}

			// The format was not found
			return "";
		}

		/** Formats the given string with the given value, returning the result */
		template <typename FirstType>
		static String Format(const String& format, const FirstType& value)
		{
			using Willow::ValueToString;

			// Iterate through the format string
			for (uint32 index = 0; index < format.Length(); ++index)
			{
				if (format[index] == '@')
				{
					return format.SubString(0, index) + ValueToString(value) + format.SubString(index + 1);
				}
			}

			return format;
		}

		/** Formats the given string with the given values, returning the result */
		template <typename FirstType, typename ... ArgTypes>
		static String Format(const String& format, const FirstType& value, const ArgTypes& ... values)
		{
			using Willow::ValueToString;

			// Iterate through the format string
			for (uint32 index = 0; index < format.Length(); ++index)
			{
				if (format[index] == '@')
				{
					return format.SubString(0, index) + ValueToString(value) + String::Format(format.SubString(index + 1), values...);
				}
			}

			return format;
		}

		/////////////////////
		///   Operators   ///
	public:

		String& operator=(const String& rhs);
		String& operator=(String&& other);
		char operator[](uint32 index) const;
		friend UTILITY_API bool operator==(const String& lhs, const String& rhs);
		friend UTILITY_API bool operator!=(const String& lhs, const String& rhs);
		friend UTILITY_API bool operator>(const String& lhs, const String& rhs);
		friend UTILITY_API bool operator>=(const String& lhs, const String& rhs);
		friend UTILITY_API bool operator<(const String& lhs, const String& rhs);
		friend UTILITY_API bool operator<=(const String& lhs, const String& rhs);
		friend UTILITY_API String operator+(const String& lhs, const String& rhs);
		friend UTILITY_API String& operator+=(String& lhs, const String& rhs);

		////////////////
		///   Data   ///
	private:

		char* _value;
	};

	/** Formats the given value as a string and returns the result */
	UTILITY_API inline String ValueToString(const String& value)
	{
		return value;
	}
	UTILITY_API String ValueToString(const object& value);
	UTILITY_API String ValueToString(const Interface& value);
	UTILITY_API String ValueToString(const char* value);
	UTILITY_API String ValueToString(const void* value);
	UTILITY_API String ValueToString(bool value);
	UTILITY_API String ValueToString(char value);
	UTILITY_API String ValueToString(byte value);
	UTILITY_API String ValueToString(int16 value);
	UTILITY_API String ValueToString(int32 value);
	UTILITY_API String ValueToString(int64 value);
	UTILITY_API String ValueToString(ubyte value);
	UTILITY_API String ValueToString(uint16 value);
	UTILITY_API String ValueToString(uint32 value);
	UTILITY_API String ValueToString(uint64 value);
	UTILITY_API String ValueToString(float value);
	UTILITY_API String ValueToString(double value);

	/** Parses the given value from a string, and returns the rest of the string */
	UTILITY_API String ValueFromString(const String& string, const void*& outValue);
	UTILITY_API String ValueFromString(const String& string, bool& outValue);
	UTILITY_API String ValueFromString(const String& string, char& outValue);
	UTILITY_API String ValueFromString(const String& string, byte& outValue);
	UTILITY_API String ValueFromString(const String& string, int16& outValue);
	UTILITY_API String ValueFromString(const String& string, int32& outValue);
	UTILITY_API String ValueFromString(const String& string, int64& outValue);
	UTILITY_API String ValueFromString(const String& string, ubyte& outValue);
	UTILITY_API String ValueFromString(const String& string, uint16& outValue);
	UTILITY_API String ValueFromString(const String& string, uint32& outValue);
	UTILITY_API String ValueFromString(const String& string, uint64& outValue);
	UTILITY_API String ValueFromString(const String& string, float& outValue);
	UTILITY_API String ValueFromString(const String& string, double& outValue);
}