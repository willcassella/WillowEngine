// String.h
#pragma once

#include "List.h"

namespace Willow
{
	struct UTILITY_API String
	{
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

		/** Returns whether this string is empty */
		bool IsNullOrEmpty() const;

		/** Returns the number of characters in this string */
		uint32 Length() const;

		/** Converts this string to a c style string */
		const char* Cstr() const;

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

		/** Returns a list of the starting indices at which the given string appears in this string */
		List<uint32> OccurencesOf(const String& string) const;

		/** If this string represents a path to a file, returns the file extension */
		String GetFileExtension() const;

		/** If this string represents a path to a file, returns the name of the file */
		String GetFileName() const;

		/** Returns the length of a c-style string */
		static uint32 Length(const char* string);

		/** Compares two c-style strings
		Return values:
		0 - stringA and stringB are equal
		<0 - stringA is alphabetically lower than stringB
		>0 - stringB is alphabetically higher than stringB */
		static int32 Compare(const char* stringA, const char* stringB, bool caseSensitive = true);

		/////////////////////
		///   Operators   ///
	public:

		String& operator=(const String& rhs);
		String& operator=(String&& other);
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
}