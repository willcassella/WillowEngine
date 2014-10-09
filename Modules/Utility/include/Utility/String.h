// String.h
#pragma once

#include "List.h"
#include "Pair.h"

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
		static String GetFileExtension(const String& path);

		/** If this string represents a path to a file, returns the name of the file */
		static String GetFileName(const String& path);

		/** Parses a string in the form 'key = value'
		* Returns a pair of the key and value
		* Returns an empty pair if the string could not be parsed*/
		static Pair<String, String> ParseEquality(const String& equality);

		/** Removes spaces from the front and end of string */
		static String RemovePadding(const String& string);

		/** Returns the length of a c-style string */
		static uint32 Length(const char* string);

		/** Compares two c-style strings
		Return values:
		0 - stringA and stringB are equal
		<0 - stringA is alphabetically lower than stringB
		>0 - stringB is alphabetically higher than stringB */
		static int32 Compare(const char* stringA, const char* stringB, bool caseSensitive = true);

		/** Attempts to parse the string as a char */
		static char ToChar(const String& string);

		/** Attempts to parse the string as an int16 */
		static int16 ToInt16(const String& string);

		/** Attempts to parse the string as an int32 */
		static int32 ToInt32(const String& string);

		/** Attempts to parse the string as an int64 */
		static int64 ToInt64(const String& string);

		/** Attempts to parse the string as a byte */
		static byte ToByte(const String& string);

		/** Attempts to parse the string as a uint16 */
		static uint16 ToUInt16(const String& string);

		/** Attempts to parse the string as a uint32 */
		static uint32 ToUint32(const String& string);

		/** Attempts to parse the string as a float */
		static float ToFloat(const String& string);

		/** Attempts to parse the string as a double */
		static double ToDouble(const String& string);

		/** Attempts to parse the string as a bool */
		static bool ToBool(const String& string);

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