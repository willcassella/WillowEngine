// String.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Containers/Tuple.h"
#include "Containers/List.h"
#include "Containers/Queue.h"
#include "Containers/Stack.h"
#include "Containers/Table.h"
#include "Operations.h"

/////////////////
///   Types   ///

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
	String(const char* value)
		: _value(value, String::Length(value) + 1)
	{
		// All done
	}

	/** Create a String from a single character */
	String(char value)
		: _value(2)
	{
		_value.Add(value);
		_value.Add('\0');
	}

private:

	/** Create a String from an array of characters */
	String(const Array<char>& arr)
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
	FORCEINLINE const char* Cstr() const
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
	static uint32 Length(const char* string);

	/** Compares two Strings
	* 'caseSensitive' : Whether to consider character case when comparing the given Strings
	* Return values:
	* 0 - 'stringA' and 'stringB' are equal 
	* <0 - 'stringA' is alphabetically lower than 'stringB' 
	* >0 - 'stringA' is alphabetically higher than 'stringB' */
	static int32 Compare(const String&, const String& stringB, bool caseSensitive = true);

	/** Formats the given String with the given value, returning the result
	* - The first instance of the '@' character in 'format' is replaced with a String representation of 'value' */
	template <typename AnyType>
	static String Format(const String& format, const AnyType& value)
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
	* - Each instance of the '@' character in 'format' is replaced with a String representation of the respective value  */
	template <typename AnyType, typename ... MoreAnyTypes>
	static String Format(const String& format, const AnyType& value, const MoreAnyTypes& ... moreValues)
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
	template <typename AnyType>
	static String Parse(const String& string, const String& format, AnyType& value)
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
	template <typename AnyType, typename ... MoreAnyTypes>
	static String Parse(const String& string, const String& format, AnyType& value, MoreAnyTypes& ... moreValues)
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

	/////////////////////
	///   Operators   ///
public:

	String& operator=(const char* rhs);
	String& operator=(char rhs);
	FORCEINLINE char operator[](uint32 index) const
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

	Array<char> _value;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Default implementation of ToExplicitString (no quotation marks) */
	template <typename AnyType>
	struct ToExplicitString
	{
		FORCEINLINE static String Function(const AnyType& value)
		{
			return ::ToString(value);
		}
	};

	///////////////////////////
	///   Primitive Types   ///

	/** Convert a bool to a String */
	template <>
	struct CORE_API ToString < bool >
	{
		static String Function(bool value);
	};

	/** Parse a bool from a String */
	template <>
	struct CORE_API FromString < bool >
	{
		static String Function(bool& value, const String& string);
	};

	/** Convert a character to a String */
	template <>
	struct CORE_API ToString < char >
	{
		static String Function(char value);
	};

	/** Parse a character from a String */
	template <>
	struct CORE_API FromString < char >
	{
		static String Function(char& value, const String& string);
	};

	/** Convert a byte to a String */
	template <>
	struct CORE_API ToString < byte >
	{
		static String Function(byte value);
	};

	/** Parse a byte from a String */
	template <>
	struct CORE_API FromString < byte >
	{
		static String Function(byte& value, const String& string);
	};

	/** Convert a 16-bit integer to a String */
	template <>
	struct CORE_API ToString < int16 >
	{
		static String Function(int16 value);
	};

	/** Parse a 16-bit integer from a String */
	template <>
	struct CORE_API FromString < int16 >
	{
		static String Function(int16& value, const String& string);
	};

	/** Convert a 32-bit integer to a String */
	template <>
	struct CORE_API ToString < int32 >
	{
		static String Function(int32 value);
	};

	/** Parse a 32-bit integer from a String */
	template <>
	struct CORE_API FromString < int32 >
	{
		static String Function(int32& value, const String& string);
	};

	/** Convert a 64-bit integer to a String */
	template <>
	struct CORE_API ToString < int64 >
	{
		static String Function(int64 value);
	};

	/** Parse a 64-bit integer from a String */
	template <>
	struct CORE_API FromString < int64 >
	{
		static String Function(int64& value, const String& string);
	};

	/** Convert an unsigned 16-bit integer to a String */
	template <>
	struct CORE_API ToString < uint16 >
	{
		static String Function(uint16 value);
	};

	/** Parse an unsigned 16-bit integer from a String */
	template <>
	struct CORE_API FromString < uint16 >
	{
		static String Function(uint16& value, const String& string);
	};

	/** Convert an unsigned 32-bit integer to a String */
	template <>
	struct CORE_API ToString < uint32 >
	{
		static String Function(uint32 value);
	};

	/** Parse an unsigned 32-bit integer from a String */
	template <>
	struct CORE_API FromString < uint32 >
	{
		static String Function(uint32& value, const String& string);
	};

	/** Convert an unsigned 64-bit integer to a String */
	template <>
	struct CORE_API ToString < uint64 >
	{
		static String Function(uint64 value);
	};

	/** Parse an unsigned 64-bit integer from a String */
	template <>
	struct CORE_API FromString < uint64 >
	{
		static String Function(uint64& value, const String& string);
	};

	/** Convert a float to a String */
	template <>
	struct CORE_API ToString < float >
	{
		static String Function(float value);
	};

	/** Parse a float from a String */
	template <>
	struct CORE_API FromString < float >
	{
		static String Function(float& value, const String& string);
	};

	/** Convert a double to a String */
	template <>
	struct CORE_API ToString < double >
	{
		static String Function(double value);
	};

	/** Parse a double from a String */
	template <>
	struct CORE_API FromString < double >
	{
		static String Function(double& value, const String& string);
	};

	/** Convert a pointer to a String */
	template <typename AnyType>
	struct ToString < AnyType* >
	{
		FORCEINLINE static String Function(const AnyType* value)
		{
			return "0xAddress"; // @TODO: Implement this
		}
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

	/** Convert a non-const c-string to a String
	* NOTE: A non-const c-string cannot be parsed from a String */
	template <>
	struct CORE_API ToString < char* >
	{
		FORCEINLINE static String Function(const char* value)
		{
			return String(value);
		}
	};

	/** Convert a non-const c-string to an explicit String */
	template <>
	struct CORE_API ToExplicitString < char* >
	{
		FORCEINLINE static String Function(const char* value)
		{
			return '"' + String(value) + '"';
		}
	};

	/** Convert a c-string to a String
	* NOTE: c-strings cannot be parsed from a String */
	template <>
	struct CORE_API ToString < const char* >
	{
		FORCEINLINE static String Function(const char* value)
		{
			return String(value);
		}
	};

	/** Convert a c-string to an explicit String */
	template <>
	struct CORE_API ToExplicitString < const char* >
	{
		FORCEINLINE static String Function(const char* value)
		{
			return '"' + String(value) + '"';
		}
	};

	/** Convert a clang/gcc c-string literal to a String
	* NOTE: A clang/gcc c-string literal cannot be parsed from a String */
	template <std::size_t size>
	struct ToString < char[size] >
	{
		FORCEINLINE static String Function(const char value[size])
		{
			return String(value);
		}
	};

	/** Convert a clang/gcc c-string literal to an Explicit String */
	template <std::size_t size>
	struct ToExplicitString < char[size] >
	{
		FORCEINLINE static String Function(const char value[size])
		{
			return '"' + String(value) + '"';
		}
	};

	/** Convert a MSVC c-string literal to a String
	* NOTE: A MSVC c-string literal cannot be parsed from a String */
	template <std::size_t size>
	struct ToString < const char[size] >
	{
		FORCEINLINE static String Function(const char value[size])
		{
			return String(value);
		}
	};

	/** Convert a MSVC c-string literal to an explicit String */
	template <std::size_t size>
	struct ToExplicitString < const char[size] >
	{
		FORCEINLINE static String Function(const char value[size])
		{
			return '"' + String(value) + '"';
		}
	};

	/** Convert a String to a String */
	template <>
	struct CORE_API ToString < String >
	{
		FORCEINLINE static String Function(const String& value)
		{
			return value;
		}
	};

	/** Convert a String to an explicit String */
	template <>
	struct CORE_API ToExplicitString < String >
	{
		FORCEINLINE static String Function(const String& value)
		{
			return '"' + value + '"';
		}
	};

	/** Parse a String from a String */
	template <>
	struct CORE_API FromString < String >
	{
		static String Function(String& value, const String& string);
	};

	///////////////////////////
	///   Container Types   ///

	/** Convert a generic container to a String */
	template <template <typename ElementType> class ContainerType, typename ElementType>
	struct ContainerToString
	{
		static String Function(const ContainerType<ElementType>& value)
		{
			String result('{');

			bool first = true;
			for (const ElementType& element : value)
			{
				if (first)
				{
					first = false;
				}
				else
				{
					result += ", ";
				}

				result += ToExplicitString<ElementType>::Function(element);
			}

			return result + '}';
		}
	};

	/** Convert an Array to a String */
	template <typename T>
	struct ToString < Array<T> >
	{
		FORCEINLINE static String Function(const Array<T>& value)
		{
			return ContainerToString<Array, T>::Function(value);
		}
	};

	/** Convert a List to a String */
	template <typename T>
	struct ToString < List<T> >
	{
		FORCEINLINE static String Function(const List<T>& value)
		{
			return ContainerToString<List, T>::Function(value);
		}
	};

	/** Convert a Queue to a String */
	template <typename T>
	struct ToString < Queue<T> >
	{
		FORCEINLINE static String Function(const Queue<T>& value)
		{
			return ContainerToString<Queue, T>::Function(value);
		}
	};

	/** Convert a Stack to a String */
	template <typename T>
	struct ToString < Stack<T> >
	{
		FORCEINLINE static String Function(const Stack<T>& value)
		{
			return ContainerToString<Stack, T>(value);
		}
	};

	/** Convert a Table to a String */
	template <typename KeyType, typename ValueType>
	struct ToString < Table<KeyType, ValueType> >
	{
		static String Function(const Table<KeyType, ValueType>& value)
		{
			String result = '{';

			bool first = true;
			for (const auto& pair : value)
			{
				if (first)
				{
					first = false;
				}
				else
				{
					result += ", ";
				}

				result += String::Format(
					"{@ : @}", 
					ToExplicitString<KeyType>::Function(pair.First), 
					ToExplicitString<ValueType>::Function(pair.Second)
				);
			}

			return result + '}';
		}
	};

	/** Convert a Pair to a String */
	template <typename FirstType, typename SecondType>
	struct ToString < Pair<FirstType, SecondType> >
	{
		FORCEINLINE static String Function(const Pair<FirstType, SecondType>& value)
		{
			return String::Format(
				"{@ | @}", 
				ToExplicitString<FirstType>::Function(value.First), 
				ToExplicitString<SecondType>::Function(value.Second)
			);
		}
	};
}