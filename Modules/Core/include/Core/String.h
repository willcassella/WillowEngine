// String.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Forwards/Operations.h"
#include "Containers/Array.h"

/** A String. Basically just an array of characters, and the
* operations associated with that. */
struct CORE_API String final
{
	////////////////////////
	///   Constructors   ///
public:

	/** Default-construct a String */
	String()
		: _value(1)
	{
		_value.Add('\0');
	}

	/** Create a String from a c-string */
	String(CString value)
		: _value(value, String::Length(value) + 1)
	{
		// All done
	}

	/** Create a String from a single character */
	String(Char value)
		: _value(2)
	{
		_value.Add(value);
		_value.Add('\0');
	}

private:

	/** Create a String from an array of characters */
	String(const Array<Char>& arr)
		: _value(arr)
	{
		_value.Add('\0');
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this String is empty */
	FORCEINLINE bool IsEmpty() const
	{
		return _value.Size() == 1;
	}

	/** Returns the number of characters in this String */
	FORCEINLINE uint32 Length() const
	{
		return _value.Size() - 1;
	}

	/** Converts this String to a c style string */
	FORCEINLINE CString Cstr() const
	{
		return &_value.First();
	}

	/** Returns a substring from the character at the start index to the end of this String
	* Returns an empty String if start is greater than the length of this String */
	FORCEINLINE String SubString(uint32 start) const
	{
		return SubString(start, Length());
	}

	/** Returns a substring from the character at the start index to the character and the end index
	* Returns an empty String if 'start' is greater than 'end' or 'start' is greater than the length of this String */
	String SubString(uint32 start, uint32 end) const;

	/** Returns a copy of this String with all upper-case characters */
	String ToUpper() const;

	/** Returns a copy of this String with all lower-case characters */
	String ToLower() const;

	/** Returns whether this String begins with the given String */
	bool StartsWith(const String& string) const;

	/** Returns whether this String ends with the given String */
	bool EndsWith(const String& string) const;

	/** Removes spaces from the front and end of 'string'
	* 'front' : whether to remove padding from the front of the String
	* 'back' : whether to remove padding from the back of the String */
	static String RemovePadding(const String& string, bool front = true, bool back = true);

	/** Returns an Array of the starting indices at which the given String appears in this String */
	Array<uint32> OccurencesOf(const String& string) const;

	/** Returns the characters of the String in opposite order */
	String Reverse() const;

	/** If the given String represents a path to a file, this parses and returns the file extension */
	static String GetFileExtension(const String& path);

	/** If the given String represents a path to a file, this parses and returns the name of the file */
	static String GetFileName(const String& path);

	/** Returns the length of a c-style string (not including null character) */
	static uint32 Length(CString string);

	/** Compares two Strings
	* 'caseSensitive' : Whether to consider character case when comparing the given Strings
	* Return values:
	* 0 - 'stringA' and 'stringB' are equal 
	* <0 - 'stringA' is alphabetically lower than 'stringB' 
	* >0 - 'stringA' is alphabetically higher than 'stringB' */
	static int32 Compare(const String&, const String& stringB, bool caseSensitive = true);

	/////////////////////
	///   Operators   ///
public:

	String& operator=(CString rhs);
	String& operator=(Char rhs);
	FORCEINLINE Char operator[](uint32 index) const
	{
		if (index < Length())
		{
			return _value[index];
		}
		else
		{
			return '\0';
		}
	}
	friend CORE_API FORCEINLINE bool operator==(const String& lhs, const String& rhs)
	{
		return lhs._value == rhs._value;
	}
	friend CORE_API FORCEINLINE bool operator!=(const String& lhs, const String& rhs)
	{
		return lhs._value != rhs._value;
	}
	friend CORE_API bool operator>(const String& lhs, const String& rhs);
	friend CORE_API FORCEINLINE bool operator>=(const String& lhs, const String& rhs)
	{
		return lhs > rhs || lhs == rhs;
	}
	friend CORE_API bool operator<(const String& lhs, const String& rhs);
	friend CORE_API FORCEINLINE bool operator<=(const String& lhs, const String& rhs)
	{
		return lhs < rhs || lhs == rhs;
	}
	friend CORE_API String operator+(const String& lhs, const String& rhs);
	friend CORE_API FORCEINLINE String& operator+=(String& lhs, const String& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	////////////////
	///   Data   ///
private:

	Array<Char> _value;
};

/** Formats the given String with the given value, returning the result
* - The first instance of the '@' character in 'format' is replaced with a String representation of 'value' */
template <typename T>
String Format(const String& format, const T& value)
{
	for (uint32 i = 0; i < format.Length(); ++i)
	{
		if (format[i] == '@')
		{
			return format.SubString(0, i) + ToString(value) + format.SubString(i + 1);
		}
	}

	// You passed in an empty format String, dumbass
	return "";
}

/** Formats the given String with the given values, returning the result
* - Each instance of the '@' character in 'format' is replaced with a String representation of the respective value. */
template <typename T, typename ... MoreT>
static String Format(const String& format, const T& value, const MoreT& ... moreValues)
{
	for (uint32 i = 0; i < format.Length(); ++i)
	{
		if (format[i] == '@')
		{
			return format.SubString(0, i) + ToString(value) + Format(format.SubString(i + 1), moreValues...);
		}
	}

	// You passed in an empty format String, dumbass
	return "";
}

/** Parses the given value from the given String, following the given format. The remainder of the String is returned.
* - The location of the '@' character in the format String denotes the location of the value in the given String */
template <typename T>
static String Parse(const String& string, const String& format, T& value)
{
	for (uint32 i = 0; i < format.Length(); ++i)
	{
		if (format[i] == '@')
		{
			return FromString(value, string.SubString(i));
		}
	}

	// You passed in an empty format String, dumbass
	return "";
}

/** Parses the given values from the given String, following the given format. The remainder of the String is returned.
* - Each location of the '@' character in the format String denotes the location of the respective value in the given String */
template <typename T, typename ... MoreT>
static String Parse(const String& string, const String& format, T& value, MoreT& ... moreValues)
{
	for (uint32 i = 0; i < format.Length(); ++i)
	{
		if (format[i] == '@')
		{
			return Parse(FromString(value, string.SubString(i)), format.SubString(i + 1), moreValues...);
		}
	}

	// You passed in an empty format String, dumbass
	return "";
}
