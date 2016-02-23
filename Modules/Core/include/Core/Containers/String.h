// String.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Array.h"

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
	FORCEINLINE std::size_t Length() const
	{
		return _value.Size() - 1;
	}

	/** Converts this String to a c style string */
	FORCEINLINE CString Cstr() const
	{
		return &_value.First();
	}

	/** Returns the character at the given index in this String. */
	FORCEINLINE Char CharAt(std::size_t index) const
	{
		return _value[index];
	}

	/** Returns a substring from the character at the start index to the end of this String
	* Returns an empty String if start is greater than the length of this String */
	FORCEINLINE String SubString(std::size_t start) const
	{
		return this->SubString(start, this->Length());
	}

	/** Returns a substring from the character at the start index to the character and the end index
	* Returns an empty String if 'start' is greater than 'end' or 'start' is greater than the length of this String */
	String SubString(std::size_t start, std::size_t end) const;

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
	Array<std::size_t> OccurencesOf(const String& string) const;

	/** Returns the characters of the String in opposite order */
	String Reverse() const;

	/** Returns the length of a c-style string (not including null character) */
	static std::size_t Length(CString string);

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
	FORCEINLINE Char operator[](std::size_t index) const
	{
		return _value[index];
	}
	friend FORCEINLINE bool operator==(const String& lhs, const String& rhs)
	{
		return lhs._value == rhs._value;
	}
	friend FORCEINLINE bool operator==(const String& lhs, CString rhs)
	{
		return lhs == String(rhs);
	}
	friend FORCEINLINE bool operator==(CString lhs, const String& rhs)
	{
		return String(lhs) == rhs;
	}
	friend FORCEINLINE bool operator!=(const String& lhs, const String& rhs)
	{
		return lhs._value != rhs._value;
	}
	friend FORCEINLINE bool operator!=(const String& lhs, CString rhs)
	{
		return lhs != String(rhs);
	}
	friend FORCEINLINE bool operator!=(CString lhs, const String& rhs)
	{
		return String(lhs) != rhs;
	}
	friend CORE_API bool operator>(const String& lhs, const String& rhs);
	friend FORCEINLINE bool operator>=(const String& lhs, const String& rhs)
	{
		return lhs > rhs || lhs == rhs;
	}
	friend CORE_API bool operator<(const String& lhs, const String& rhs);
	friend FORCEINLINE bool operator<=(const String& lhs, const String& rhs)
	{
		return lhs < rhs || lhs == rhs;
	}
	friend CORE_API String operator+(const String& lhs, const String& rhs);
	friend FORCEINLINE String& operator+=(String& lhs, const String& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	////////////////
	///   Data   ///
private:

	Array<Char> _value;
};

/////////////////////
///   Functions   ///

/** Custom operator for String literals. */
FORCEINLINE String operator"" _s(CString string, std::size_t /*size*/)
{
	return String(string);
}
