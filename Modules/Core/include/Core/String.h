// String.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
/** All code for creating and manipulating Strings lives here */
#pragma once

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
inline String ToString(const AnyType&);

/** Defined below */
template <typename AnyType>
inline String FromString(AnyType&, const String&);

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
	inline bool IsEmpty() const
	{
		return _value.Size() == 1;
	}

	/** Returns the number of characters in this String */
	inline uint32 Length() const
	{
		return _value.Size() - 1;
	}

	/** Converts this String to a c style string */
	inline const char* Cstr() const
	{
		return &_value.First();
	}

	/** Returns a substring from the character at the start index to the end of this String
	* Returns an empty String if start is greater than the length of this String */
	inline String SubString(uint32 start) const
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
	static String Parse(const String& format, const String& string, AnyType& value)
	{
		for (uint32 i = 0; i < format.Length(); ++i)
		{
			if (format[i] == '@')
			{
				return FromString(value, string[i]);
			}
		}

		// You passed in an empty format String, dumbass
		return "";
	}

	/** Parses the given values from the given String, following the given format. The remainder of the String is returned.
	* - Each location of the '@' character in the format String denotes the location of the respective value in the given String */
	template <typename AnyType, typename ... MoreAnyTypes>
	static String Parse(const String& format, const String& string, AnyType& value, MoreAnyTypes& ... moreValues)
	{
		for (uint32 i = 0; i < format.Length(); ++i)
		{
			if (format[i] == '@')
			{
				return Parse(format.SubString(i + 1), FromString(value, string[i]), moreValues...);
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
	inline char operator[](uint32 index) const
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
	friend CORE_API inline bool operator==(const String& lhs, const String& rhs)
	{
		return lhs._value == rhs._value;
	}
	friend CORE_API inline bool operator!=(const String& lhs, const String& rhs)
	{
		return lhs._value != rhs._value;
	}
	friend CORE_API bool operator>(const String& lhs, const String& rhs);
	friend CORE_API inline bool operator>=(const String& lhs, const String& rhs)
	{
		return lhs > rhs || lhs == rhs;
	}
	friend CORE_API bool operator<(const String& lhs, const String& rhs);
	friend CORE_API inline bool operator<=(const String& lhs, const String& rhs)
	{
		return lhs < rhs || lhs == rhs;
	}
	friend CORE_API String operator+(const String& lhs, const String& rhs);
	friend CORE_API inline String& operator+=(String& lhs, const String& rhs)
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
		inline static String Function(const AnyType& value)
		{
			return value.ToString();
		}
	};

	/** Default implementation of FromString */
	template <typename AnyType>
	struct FromString
	{
		inline static String Function(AnyType& value, const String& string)
		{
			return AnyType::FromString(value, string);
		}
	};

	///////////////////////////
	///   Primitive Types   ///

	/** Convert a generic integer to a String (used in the ToString specializations for integer types) */
	template <typename IntType>
	String IntToString(IntType value)
	{
		String result;

		if (value < 0)
		{
			result = '-';
			value *= -1;
		}
			
		if (value == 0)
		{
			return '0';
		}

		while (value != 0)
		{
			IntType digit = value % 10;

			switch (digit)
			{
			case 0:
				result += '0';
				break;
			case 1:
				result += '1';
				break;
			case 2:
				result += '2';
				break;
			case 3:
				result += '3';
				break;
			case 4:
				result += '4';
				break;
			case 5:
				result += '5';
				break;
			case 6:
				result += '6';
				break;
			case 7:
				result += '7';
				break;
			case 8:
				result += '8';
				break;
			case 9:
				result += '9';
			}

			value /= 10;
		}

		return result.Reverse();
	}

	/** Parse a generic int from a String (used in the FromString specializations for integer types) */
	template <typename IntType>
	String IntFromString(IntType& value, const String& string)
	{
		value = 0;

		for (uint32 i = 0; i < string.Length(); ++i)
		{
			if (string[i] == ' ')
			{
				return string[i];
			}

			value *= 10;
			char character = string[i];

			switch (character)
			{
			case '0':
				break;
			case '1':
				value += 1;
				break;
			case '2':
				value += 2;
				break;
			case '3':
				value += 3;
				break;
			case '4':
				value += 4;
				break;
			case '5':
				value += 5;
				break;
			case '6':
				value += 6;
				break;
			case '7':
				value += 7;
				break;
			case '8':
				value += 8;
				break;
			case '9':
				value += 9;
				break;
			}
		}

		return "";
	}

	/** Convert a float to a String (using 'std::to_string' internally) */
	CORE_API String FloatToString(float value);

	/** Parse a float from a String (using 'std::stof' internally) */
	CORE_API String FloatFromString(float& value, const String& string);

	/** Convert a double to a String (using 'std::to_string' internally) */
	CORE_API String DoubleToString(double value);

	/** Parse a double from a String (using 'std::stod' internally) */
	CORE_API String DoubleFromString(double& value, const String& string);

	/** Convert a bool to a String */
	template <>
	struct ToString < bool >
	{
		inline static String Function(bool value)
		{
			if (value)
			{
				return "true";
			}
			else
			{
				return "false";
			}
		}
	};

	/** Parse a bool from a String */
	template <>
	struct FromString < bool >
	{
		static String Function(bool& value, const String& string)
		{
			String head = string.SubString(0, 6).ToLower();

			if (head.StartsWith("true"))
			{
				value = true;
				return string.SubString(4);
			}
			else if (head.StartsWith("false"))
			{
				value = false;
				return string.SubString(5);
			}
			else
			{
				return string;
			}
		}
	};

	/** Convert a character to a String */
	template <>
	struct ToString < char >
	{
		static String Function(char value)
		{
			return String(value);
		}
	};

	/** Parse a character from a String */
	template <>
	struct FromString < char >
	{
		static String Function(char& value, const String& string)
		{
			// Characters in strings must be wrapped with the ' character
			if (string.StartsWith("'"))
			{
				value = string[1];
				return string[3];
			}
			else
			{
				return string;
			}
		}
	};

	/** Convert a byte to a String */
	template <>
	struct ToString < byte >
	{
		inline static String Function(byte value)
		{
			return IntToString(value);
		}
	};

	/** Parse a byte from a String */
	template <>
	struct FromString < byte >
	{
		inline static String Function(byte& value, const String& string)
		{
			return IntFromString(value, string);
		}
	};

	/** Convert a 16-bit integer to a String */
	template <>
	struct ToString < int16 >
	{
		inline static String Function(int16 value)
		{
			return IntToString(value);
		}
	};

	/** Parse a 16-bit integer from a String */
	template <>
	struct FromString < int16 >
	{
		inline static String Function(int16& value, const String& string)
		{
			return IntFromString(value, string);
		}
	};

	/** Convert a 32-bit integer to a String */
	template <>
	struct ToString < int32 >
	{
		inline static String Function(int32 value)
		{
			return IntToString(value);
		}
	};

	/** Parse a 32-bit integer from a String */
	template <>
	struct FromString < int32 >
	{
		inline static String Function(int32& value, const String& string)
		{
			return IntFromString(value, string);
		}
	};

	/** Convert a 64-bit integer to a String */
	template <>
	struct ToString < int64 >
	{
		inline static String Function(int64 value)
		{
			return IntToString(value);
		}
	};

	/** Parse a 64-bit integer from a String */
	template <>
	struct FromString < int64 >
	{
		inline static String Function(int64& value, const String& string)
		{
			return IntFromString(value, string);
		}
	};

	/** Convert an unsigned 16-bit integer to a String */
	template <>
	struct ToString < uint16 >
	{
		inline static String Function(uint16 value)
		{
			return IntToString(value);
		}
	};

	/** Parse an unsigned 16-bit integer from a String */
	template <>
	struct FromString < uint16 >
	{
		inline static String Function(uint16& value, const String& string)
		{
			return IntFromString(value, string);
		}
	};

	/** Convert an unsigned 32-bit integer to a String */
	template <>
	struct ToString < uint32 >
	{
		inline static String Function(uint32 value)
		{
			return IntToString(value);
		}
	};

	/** Parse an unsigned 32-bit integer from a String */
	template <>
	struct FromString < uint32 >
	{
		inline static String Function(uint32& value, const String& string)
		{
			return IntFromString(value, string);
		}
	};

	/** Convert an unsigned 64-bit integer to a String */
	template <>
	struct ToString < uint64 >
	{
		inline static String Function(uint64 value)
		{
			return IntToString(value);
		}
	};

	/** Parse an unsigned 64-bit integer from a String */
	template <>
	struct FromString < uint64 >
	{
		inline static String Function(uint64& value, const String& string)
		{
			return IntFromString(value, string);
		}
	};

	/** Convert a float to a String */
	template <>
	struct ToString < float >
	{
		inline static String Function(float value)
		{
			return FloatToString(value);
		}
	};

	/** Parse a float from a String */
	template <>
	struct FromString < float >
	{
		inline static String Function(float& value, const String& string)
		{
			return FloatFromString(value, string);
		}
	};

	/** Convert a double to a String */
	template <>
	struct ToString < double >
	{
		inline static String Function(double value)
		{
			return DoubleToString(value);
		}
	};

	/** Parse a double from a String */
	template <>
	struct FromString < double >
	{
		inline static String Function(double& value, const String& string)
		{
			return DoubleFromString(value, string);
		}
	};

	/** Convert a pointer to a String */
	template <typename AnyType>
	struct ToString < AnyType* >
	{
		inline static String Function(const AnyType* value)
		{
			// @TODO: Redo this
			return "0x" + ::ToString(reinterpret_cast<PtrType>(value));
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
				String valueString = string.SubString(2);
				PtrType numericValue;

				String remainingString = ::FromString(numericValue, valueString);
					
				value = reinterpret_cast<const AnyType*>(numericValue);
				return remainingString;
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
	struct ToString < const char* >
	{
		inline static String Function(const char* value)
		{
			return String(value);
		}
	};

	/** Convert a MSVC c-string literal to a String
	* NOTE: A MSVC c-string literal cannot be parsed from a String */
	template <std::size_t size>
	struct ToString < const char[size] >
	{
		inline static String Function(const char value[size])
		{
			return String(value);
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
		inline static String Function(const Array<T>& value)
		{
			return ContainerToString<Array<T>, T>::Function(value);
		}
	};

	/** Parse an Array from a String */
	template <typename T>
	struct FromString < Array<T> >
	{
		inline static String Function(Array<T>& value, const String& string)
		{
			value.Clear();
			return ContainerFromString<Array<T>, T>::Function(value, &Array<T>::Add, string);
		}
	};

	/** Convert a List to a String */
	template <typename T>
	struct ToString < List<T> >
	{
		inline static String Function(const List<T>& value)
		{
			return ContainerToString<List<T>, T>::Function(value);
		}
	};

	/** Parse a List from a String */
	template <typename T>
	struct FromString < List<T> >
	{
		inline static String Function(List<T>& value, const String& string)
		{
			value.Clear();
			return ContainerFromString<List<T>, T>::Function(value, &List<T>::Add, string);
		}
	};

	///** Convert an ArrayList to a String */
	//template <typename T>
	//struct ToString < ArrayList<T> >
	//{
	//	inline static String Function(const ArrayList<T>& value)
	//	{
	//		return ContainerToString(value);
	//	}
	//};

	///** Parse an ArrayList from a String */
	//template <typename T>
	//struct FromString < ArrayList<T> >
	//{
	//	inline static String Function(ArrayList<T>& value, const String& string)
	//	{
	//		return ContainerFromString(value, string);
	//	}
	//};

	/** Convert a Queue to a String */
	template <typename T, template <typename F> class StorageType>
	struct ToString < Queue<T, StorageType> >
	{
		inline static String Function(const Queue<T, StorageType>& value)
		{
			return ContainerToString<Queue<T, StorageType>, T>::Function(value);
		}
	};

	/** Parse a Queue from a String */
	template <typename T, template <typename F> class StorageType>
	struct FromString < Queue<T, StorageType> >
	{
		inline static String Function(Queue<T, StorageType>& value, const String& string)
		{
			value.Clear();
			return ContainerFromString<Queue<T, StorageType>, T>::Function(value, &Queue<T, StorageType>::Push, string);
		}
	};

	/** Convert a Stack to a String */
	template <typename T, template <typename F> class StorageType>
	struct ToString < Stack<T, StorageType> >
	{
		inline static String Function(const Stack<T, StorageType>& value)
		{
			return ContainerToString<Stack<T, StorageType>, T>(value);
		}
	};

	/** Parse a Stack from a String */
	template <typename T, template <typename F> class StorageType>
	struct FromString < Stack<T, StorageType> >
	{
		inline static String Function(Stack<T, StorageType>& value, const String& string)
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
			// @TODO: Implement this
			return "";
		}
	};

	/** Convert a Pair to a String */
	template <typename A, typename B>
	struct ToString < Pair<A, B> >
	{
		inline static String Function(const Pair<A, B>& value)
		{
			return String::Format("{@ | @}", value.First, value.Second);
		}
	};

	/** Convert a Pair with A as a String to a String */
	template <typename B>
	struct ToString < Pair<String, B> >
	{
		inline static String Function(const Pair<String, B>& value)
		{
			return String::Format("{\"@\" | @}", value.First, value.Second);
		}
	};

	/** Convert a Pair with B as a String to a String */
	template <typename A>
	struct ToString < Pair<A, String> >
	{
		inline static String Function(const Pair<A, String>& value)
		{
			return String::Format("{@ | \"@\"}", value.First, value.Second);
		}
	};

	/** Convert a Pair of Strings to a String */
	template <>
	struct ToString < Pair<String, String> >
	{
		inline static String Function(const Pair<String, String>& value)
		{
			return String::Format("{\"@\" | \"@\"}", value.First, value.Second);
		}
	};

	/** Parse a Pair from a String */
	template <typename A, typename B>
	struct FromString < Pair<A, B> >
	{
		inline static String Function(Pair<A, B>& value, const String& string)
		{
			return String::Parse("{@ | @}", string, value.First, value.Second);
		}
	};

	/** Convert a String to a String */
	template <>
	struct ToString < String >
	{
		inline static String Function(const String& value)
		{
			return value;
		}
	};

	/** Parse a String from a String */
	template <>
	struct FromString < String >
	{
		static String Function(String& value, const String& string)
		{
			// @TODO: Implement this
			return "";
		}
	};
}

/////////////////////
///   Functions   ///

/** Converts the given value to a String 
* DO NOT OVERLOAD: Specialize struct Implementation::ToString */
template <typename AnyType>
inline String ToString(const AnyType& value)
{
	return Implementation::ToString<AnyType>::Function(value);
}
	
/** Parse the given String as the given value's type, returning the remaining String 
* DO NOT OVERLOAD: Specialize struct Implementation::FromString */
template <typename AnyType>
inline String FromString(AnyType& value, const String& string)
{
	return Implementation::FromString<AnyType>::Function(value, string);
}