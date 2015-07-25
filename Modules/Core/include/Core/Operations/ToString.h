// ToString.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Containers/List.h"
#include "../Containers/Stack.h"
#include "../Containers/Queue.h"
#include "../Containers/Table.h"
#include "../String.h"

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Default Implementation of 'ToString', defined in 'Reflection/TypeInfo.h' */
	template <typename T>
	struct ToString;

	/** Default implementation of ToExplicitString (no quotation marks) */
	template <typename T>
	struct ToExplicitString final
	{
		FORCEINLINE static String Function(const T& value)
		{
			return ::ToString(value);
		}
	};

	///////////////////////////
	///   Primitive Types   ///

	/** Convert a bool to a String */
	template <>
	struct CORE_API ToString < bool > final
	{
		static String Function(bool value);
	};

	/** Convert a character to a String */
	template <>
	struct CORE_API ToString < char > final
	{
		static String Function(char value);
	};

	/** Convert a byte to a String */
	template <>
	struct CORE_API ToString < byte > final
	{
		static String Function(byte value);
	};

	/** Convert a 16-bit integer to a String */
	template <>
	struct CORE_API ToString < int16 > final
	{
		static String Function(int16 value);
	};

	/** Convert a 32-bit integer to a String */
	template <>
	struct CORE_API ToString < int32 > final
	{
		static String Function(int32 value);
	};

	/** Convert a 64-bit integer to a String */
	template <>
	struct CORE_API ToString < int64 > final
	{
		static String Function(int64 value);
	};

	/** Convert an unsigned 16-bit integer to a String */
	template <>
	struct CORE_API ToString < uint16 > final
	{
		static String Function(uint16 value);
	};

	/** Convert an unsigned 32-bit integer to a String */
	template <>
	struct CORE_API ToString < uint32 > final
	{
		static String Function(uint32 value);
	};

	/** Convert an unsigned 64-bit integer to a String */
	template <>
	struct CORE_API ToString < uint64 > final
	{
		static String Function(uint64 value);
	};

	/** Convert a float to a String */
	template <>
	struct CORE_API ToString < float > final
	{
		static String Function(float value);
	};

	/** Convert a double to a String */
	template <>
	struct CORE_API ToString < double > final
	{
		static String Function(double value);
	};

	/** Convert a pointer to a String */
	template <typename T>
	struct ToString < T* > final
	{
		FORCEINLINE static String Function(T* /*value*/)
		{
			return "0xAddress"; // @TODO: Implement this
		}
	};

	////////////////////////
	///   String Types   ///

	/** Convert a non-const c-string to a String
	* NOTE: A non-const c-string cannot be parsed from a String */
	template <>
	struct ToString < char* > final
	{
		FORCEINLINE static String Function(const char* value)
		{
			return String(value);
		}
	};

	/** Convert a non-const c-string to an explicit String */
	template <>
	struct ToExplicitString < char* > final
	{
		FORCEINLINE static String Function(const char* value)
		{
			return String('"') + String(value) + String('"');
		}
	};

	/** Convert a c-string to a String
	* NOTE: c-strings cannot be parsed from a String */
	template <>
	struct ToString < const char* > final
	{
		FORCEINLINE static String Function(const char* value)
		{
			return String(value);
		}
	};

	/** Convert a c-string to an explicit String */
	template <>
	struct ToExplicitString < const char* > final
	{
		FORCEINLINE static String Function(const char* value)
		{
			return String('"') + String(value) + String('"');
		}
	};

	/** Convert a clang/gcc c-string literal to a String
	* NOTE: A clang/gcc c-string literal cannot be parsed from a String */
	template <std::size_t size>
	struct ToString < char[size] > final
	{
		FORCEINLINE static String Function(const char value[size])
		{
			return String(value);
		}
	};

	/** Convert a clang/gcc c-string literal to an Explicit String */
	template <std::size_t size>
	struct ToExplicitString < char[size] > final
	{
		FORCEINLINE static String Function(const char value[size])
		{
			return '"' + String(value) + '"';
		}
	};

	/** Convert a MSVC c-string literal to a String
	* NOTE: A MSVC c-string literal cannot be parsed from a String */
	template <std::size_t size>
	struct ToString < const char[size] > final
	{
		FORCEINLINE static String Function(const char value[size])
		{
			return String(value);
		}
	};

	/** Convert a MSVC c-string literal to an explicit String @TODO: Determine if this can be removed */
	template <std::size_t size>
	struct ToExplicitString < const char[size] > final
	{
		FORCEINLINE static String Function(const char value[size])
		{
			return '"' + String(value) + '"';
		}
	};

	/** Convert a String to a String */
	template <>
	struct ToString < String > final
	{
		FORCEINLINE static String Function(const String& value)
		{
			return value;
		}
	};

	/** Convert a String to an explicit String */
	template <>
	struct ToExplicitString < String > final
	{
		FORCEINLINE static String Function(const String& value)
		{
			return String('"') + value + String('"');
		}
	};

	///////////////////////////
	///   Container Types   ///

	/** Convert a generic container to a String */
	template <template <typename ElementType> class ContainerType, typename ElementType>
	struct ContainerToString final
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
	struct ToString < Array<T> > final
	{
		FORCEINLINE static String Function(const Array<T>& value)
		{
			return ContainerToString<Array, T>::Function(value);
		}
	};

	/** Convert a List to a String */
	template <typename T>
	struct ToString < List<T> > final
	{
		FORCEINLINE static String Function(const List<T>& value)
		{
			return ContainerToString<List, T>::Function(value);
		}
	};

	/** Convert a Queue to a String */
	template <typename T>
	struct ToString < Queue<T> > final
	{
		FORCEINLINE static String Function(const Queue<T>& value)
		{
			return ContainerToString<Queue, T>::Function(value);
		}
	};

	/** Convert a Stack to a String */
	template <typename T>
	struct ToString < Stack<T> > final
	{
		FORCEINLINE static String Function(const Stack<T>& value)
		{
			return ContainerToString<Stack, T>(value);
		}
	};

	/** Convert a Table to a String */
	template <typename KeyType, typename ValueType>
	struct ToString < Table<KeyType, ValueType> > final
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

				result += Format(
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
	struct ToString < Pair<FirstType, SecondType> > final
	{
		FORCEINLINE static String Function(const Pair<FirstType, SecondType>& value)
		{
			return Format(
				"{@ | @}",
				ToExplicitString<FirstType>::Function(value.First),
				ToExplicitString<SecondType>::Function(value.Second)
				);
		}
	};
}

/////////////////////
///   Functions   ///

/** Formats the given String with the given value, returning the result
* - The first instance of the '@' character in 'format' is replaced with a String representation of 'value' */
template <typename T>
String ToString(const String& format, const T& value)
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
String ToString(const String& format, const T& value, const MoreT& ... moreValues)
{
	for (uint32 i = 0; i < format.Length(); ++i)
	{
		if (format[i] == '@')
		{
			return format.SubString(0, i) + ToString(value) + ToString(format.SubString(i + 1), moreValues...);
		}
	}

	// You passed in an empty format String, dumbass
	return "";
}
