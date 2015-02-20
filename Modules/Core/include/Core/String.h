// String.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
/** All code for creating and manipulating Strings lives here */
#pragma once

#include "Containers/Tuple.h"
#include "Containers/List.h"
#include "Containers/Queue.h"
#include "Containers/Stack.h"
#include "Containers/Table.h"

////////////////////////////////
///   Forward declarations   ///

/** Defined below */
struct String;

/** Defined below */
template <typename AnyType>
FORCEINLINE String ToString(const AnyType&);

/** Defined below */
template <typename AnyType>
FORCEINLINE String FromString(AnyType&, const String&);

/////////////////
///   Types   ///

/** A String. Basically just an array of characters, and the
* operations associated with that. */
struct CORE_API String
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
	///////////////////////////////////
	///   Default Implementations   ///

	/** Default implementation of ToString */
	template <typename AnyType>
	struct ToString
	{
		FORCEINLINE static String Function(const AnyType& value)
		{
			return value.ToString();
		}
	};

	/** Default implementation of FromString */
	template <typename AnyType>
	struct FromString
	{
		FORCEINLINE static String Function(AnyType& value, const String& string)
		{
			return AnyType::FromString(value, string);
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
			PointerT address = reinterpret_cast<PointerT>(value);
			String result = "0x";

			return result + "address"; // @TODO: Implement this
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

	/** Convert a String to a String */
	template <>
	struct CORE_API ToString < String >
	{
		FORCEINLINE static String Function(const String& value)
		{
			return value;
		}
	};

	/** Parse a String from a String */
	template <>
	struct CORE_API FromString < String >
	{
		static String Function(String& value, const String& string)
		{
			// @TODO: Implement this
			return "";
		}
	};

	///////////////////////////
	///   Container Types   ///

	/** Convert a generic container to a String */
	template <typename ContainerType, typename ElementType>
	struct ContainerToString
	{
		static String Function(const ContainerType& value)
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

				result += ::ToString(element);
			}

			return result + '}';
		}
	};

	/** Convert a generic container of Strings to a String */
	template <typename ContainerType>
	struct ContainerToString < ContainerType, String >
	{
		static String Function(const ContainerType& value)
		{
			String result('{');

			bool first = true;
			for (const String& element : value)
			{
				if (first)
				{
					first = false;
				}
				else
				{
					result += ", ";
				}

				result += '"' + element + '"';
			}

			return result + '}';
		}
	};

	/** Parse a generic container from a String */
	template <typename ContainerType, typename ElementType>
	struct ContainerFromString
	{
		static String Function(ContainerType& value, void(ContainerType::*addFunc)(const ElementType&), const String& string)
		{
			if (string.StartsWith('{'))
			{
				while (true)
				{

				}
			}
			else
			{
				return string;
			}
		}
	};

	/** Convert an Array to a String */
	template <typename T>
	struct ToString < Array<T> >
	{
		FORCEINLINE static String Function(const Array<T>& value)
		{
			return ContainerToString<Array<T>, T>::Function(value);
		}
	};

	/** Parse an Array from a String */
	template <typename T>
	struct FromString < Array<T> >
	{
		FORCEINLINE static String Function(Array<T>& value, const String& string)
		{
			value.Clear();
			return ContainerFromString<Array<T>, T>::Function(value, &Array<T>::Add, string);
		}
	};

	/** Convert a List to a String */
	template <typename T>
	struct ToString < List<T> >
	{
		FORCEINLINE static String Function(const List<T>& value)
		{
			return ContainerToString<List<T>, T>::Function(value);
		}
	};

	/** Parse a List from a String */
	template <typename T>
	struct FromString < List<T> >
	{
		FORCEINLINE static String Function(List<T>& value, const String& string)
		{
			value.Clear();
			return ContainerFromString<List<T>, T>::Function(value, &List<T>::Add, string);
		}
	};

	///** Convert an ArrayList to a String */
	//template <typename T>
	//struct ToString < ArrayList<T> >
	//{
	//	FORCEINLINE static String Function(const ArrayList<T>& value)
	//	{
	//		return ContainerToString(value);
	//	}
	//};

	///** Parse an ArrayList from a String */
	//template <typename T>
	//struct FromString < ArrayList<T> >
	//{
	//	FORCEINLINE static String Function(ArrayList<T>& value, const String& string)
	//	{
	//		return ContainerFromString(value, string);
	//	}
	//};

	/** Convert a Queue to a String */
	template <typename T, template <typename F> class StorageType>
	struct ToString < Queue<T, StorageType> >
	{
		FORCEINLINE static String Function(const Queue<T, StorageType>& value)
		{
			return ContainerToString<Queue<T, StorageType>, T>::Function(value);
		}
	};

	/** Parse a Queue from a String */
	template <typename T, template <typename F> class StorageType>
	struct FromString < Queue<T, StorageType> >
	{
		FORCEINLINE static String Function(Queue<T, StorageType>& value, const String& string)
		{
			value.Clear();
			return ContainerFromString<Queue<T, StorageType>, T>::Function(value, &Queue<T, StorageType>::Push, string);
		}
	};

	/** Convert a Stack to a String */
	template <typename T, template <typename F> class StorageType>
	struct ToString < Stack<T, StorageType> >
	{
		FORCEINLINE static String Function(const Stack<T, StorageType>& value)
		{
			return ContainerToString<Stack<T, StorageType>, T>(value);
		}
	};

	/** Parse a Stack from a String */
	template <typename T, template <typename F> class StorageType>
	struct FromString < Stack<T, StorageType> >
	{
		FORCEINLINE static String Function(Stack<T, StorageType>& value, const String& string)
		{
			value.Clear();
			return ContainerFromString<Stack<T, StorageType>, T>::Function(value, &Stack<T, StorageType>::Push, string);
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

				result += String::Format("{@ : @}", pair.First, pair.Second);
			}

			return result + '}';
		}
	};

	/** Convert a Table with Strings as keys to a String */
	template <typename ValueType>
	struct ToString < Table<String, ValueType> >
	{
		static String Function(const Table<String, ValueType>& value)
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

				result += String::Format("{\"@\" : @}", pair.First, pair.Second);
			}

			return result + '}';
		}
	};

	/** Convert a Table with Strings as values to a String */
	template <typename KeyType>
	struct ToString < Table<KeyType, String> >
	{
		static String Function(const Table<KeyType, String>& value)
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

				result += String::Format("{@ : \"@\"}", pair.First, pair.Second);
			}

			return result + '}';
		}
	};

	/** Convert a Table with Strings as keys and values to a String */
	template <>
	struct ToString < Table<String, String> >
	{
		static String Function(const Table<String, String>& value)
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

				result += String::Format("{\"@\" : \"@\"}", pair.First, pair.Second);
			}

			return result + '}';
		}
	};

	/** Parse a Table from a String */
	template <typename KeyType, typename ValueType>
	struct FromString < Table<KeyType, ValueType> >
	{
		static String Function(Table<KeyType, ValueType>& value, const String& string)
		{
			value.Clear();
			return string; // @TODO: Implement this
		}
	};

	/** Convert a Pair to a String */
	template <typename FirstType, typename SecondType>
	struct ToString < Pair<FirstType, SecondType> >
	{
		FORCEINLINE static String Function(const Pair<FirstType, SecondType>& value)
		{
			return String::Format("{@ | @}", value.First, value.Second);
		}
	};

	/** Convert a Pair with 'FirstType' as a String to a String */
	template <typename SecondType>
	struct ToString < Pair<String, SecondType> >
	{
		FORCEINLINE static String Function(const Pair<String, SecondType>& value)
		{
			return String::Format("{\"@\" | @}", value.First, value.Second);
		}
	};

	/** Convert a Pair with 'SecondType' as a String to a String */
	template <typename FirstType>
	struct ToString < Pair<FirstType, String> >
	{
		FORCEINLINE static String Function(const Pair<FirstType, String>& value)
		{
			return String::Format("{@ | \"@\"}", value.First, value.Second);
		}
	};

	/** Convert a Pair of Strings to a String */
	template <>
	struct ToString < Pair<String, String> >
	{
		FORCEINLINE static String Function(const Pair<String, String>& value)
		{
			return String::Format("{\"@\" | \"@\"}", value.First, value.Second);
		}
	};

	/** Parse a Pair from a String */
	template <typename FirstType, typename SecondType>
	struct FromString < Pair<FirstType, SecondType> >
	{
		FORCEINLINE static String Function(Pair<FirstType, SecondType>& value, const String& string)
		{
			return String::Parse(string, "{@ | @}", value.First, value.Second);
		}
	};
}

/////////////////////
///   Functions   ///

/** Converts the given value to a String 
* DO NOT OVERLOAD: Specialize struct Implementation::ToString */
template <typename AnyType>
FORCEINLINE String ToString(const AnyType& value)
{
	return Implementation::ToString<AnyType>::Function(value);
}

/** Parse the given String as the given value's type, returning the remaining String 
* DO NOT OVERLOAD: Specialize struct Implementation::FromString */
template <typename AnyType>
FORCEINLINE String FromString(AnyType& value, const String& string)
{
	return Implementation::FromString<AnyType>::Function(value, string);
}