// ToString.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Containers/List.h"
#include "../Containers/Stack.h"
#include "../Containers/Queue.h"
#include "../Containers/Table.h"
#include "../Reflection/TypeInfo.h"

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

	/** Convert a character to a String */
	template <>
	struct CORE_API ToString < char >
	{
		static String Function(char value);
	};

	/** Convert a byte to a String */
	template <>
	struct CORE_API ToString < byte >
	{
		static String Function(byte value);
	};

	/** Convert a 16-bit integer to a String */
	template <>
	struct CORE_API ToString < int16 >
	{
		static String Function(int16 value);
	};

	/** Convert a 32-bit integer to a String */
	template <>
	struct CORE_API ToString < int32 >
	{
		static String Function(int32 value);
	};

	/** Convert a 64-bit integer to a String */
	template <>
	struct CORE_API ToString < int64 >
	{
		static String Function(int64 value);
	};

	/** Convert an unsigned 16-bit integer to a String */
	template <>
	struct CORE_API ToString < uint16 >
	{
		static String Function(uint16 value);
	};

	/** Convert an unsigned 32-bit integer to a String */
	template <>
	struct CORE_API ToString < uint32 >
	{
		static String Function(uint32 value);
	};

	/** Convert an unsigned 64-bit integer to a String */
	template <>
	struct CORE_API ToString < uint64 >
	{
		static String Function(uint64 value);
	};

	/** Convert a float to a String */
	template <>
	struct CORE_API ToString < float >
	{
		static String Function(float value);
	};

	/** Convert a double to a String */
	template <>
	struct CORE_API ToString < double >
	{
		static String Function(double value);
	};

	/** Convert a pointer to a String */
	template <typename AnyType>
	struct ToString < AnyType* >
	{
		FORCEINLINE static String Function(AnyType* value)
		{
			return "0xAddress"; // @TODO: Implement this
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

	/** Convert a MSVC c-string literal to an explicit String @TODO: Determine if this can be removed */
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
