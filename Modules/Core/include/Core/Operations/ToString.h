// ToString.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <cstdlib>
#include <cstring>
#include "../Forwards/Operations.h"
#include "../Containers/Array.h"
#include "../Containers/List.h"
#include "../Containers/Queue.h"
#include "../Containers/Stack.h"
#include "../Containers/Table.h"
#include "../Containers/Pair.h"
#include "../String.h"

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Generic implementation of 'ToString' */
	template <typename T>
	struct ToString final
	{
	private:

		/** Implementation for if the type defines its own "ToString" method (preferred). */
		template <typename F>
		FORCEINLINE static auto Impl(Preferred, const F& value) -> decltype(value.F::ToString())
		{
			return value.ToString();
		}

		/** Implementation for if the type does not define its own "ToString" method (fallback). */
		template <typename F>
		FORCEINLINE static auto Impl(Fallback, const F& value) -> String
		{
			return Default::ToString(value);
		}

	public:

		/** Entry point for the implementation. */
		FORCEINLINE static String Function(const T& value)
		{
			using ReturnType = decltype(Impl(0, value));
			static_assert(std::is_same<String, ReturnType>::value || std::is_same<const String&, ReturnType>::value,
				"The return type of the 'ToString' method must be either a 'String' or a const reference to one.");

			return Impl(0, value);
		}
	};

	/** Generic implementation of 'ToExplicitString' (no quotation marks) */
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

	/** Implementation of 'ToString' for bool */
	template <>
	struct CORE_API ToString < bool > final
	{
		static String Function(bool value);
	};

	/** Implementation of 'ToString' for char */
	template <>
	struct CORE_API ToString < char > final
	{
		static String Function(char value);
	};

	/** Implementation of 'ToString' for byte */
	template <>
	struct CORE_API ToString < byte > final
	{
		static String Function(byte value);
	};

	/** Implementation of 'ToString' for int16 */
	template <>
	struct CORE_API ToString < int16 > final
	{
		static String Function(int16 value);
	};

	/** Implementation of 'ToString' for int32 */
	template <>
	struct CORE_API ToString < int32 > final
	{
		static String Function(int32 value);
	};

	/** Implementation of 'ToString' for int64 */
	template <>
	struct CORE_API ToString < int64 > final
	{
		static String Function(int64 value);
	};

	/** Implementation of 'ToString' for uint16 */
	template <>
	struct CORE_API ToString < uint16 > final
	{
		static String Function(uint16 value);
	};

	/** Implementation of 'ToString' for uint32 */
	template <>
	struct CORE_API ToString < uint32 > final
	{
		static String Function(uint32 value);
	};

	/** Implementation of 'ToString' for uint64 */
	template <>
	struct CORE_API ToString < uint64 > final
	{
		static String Function(uint64 value);
	};

	/** Implementation of 'ToString' for float */
	template <>
	struct CORE_API ToString < float > final
	{
		static String Function(float value);
	};

	/** Implementation of 'ToString' for double */
	template <>
	struct CORE_API ToString < double > final
	{
		static String Function(double value);
	};

	/** Implementation of 'ToString' for long double */
	template <>
	struct CORE_API ToString < long double > final
	{
		static String Function(long double value);
	};

	/** Implementation of 'ToString' for pointers */
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

	/** Implementation of 'ToString' for non-const c-strings */
	template <>
	struct ToString < char* > final
	{
		FORCEINLINE static String Function(const char* value)
		{
			return String(value);
		}
	};

	/** Implementation of 'ToExplicitString' for c-strings  */
	template <>
	struct ToExplicitString < char* > final
	{
		FORCEINLINE static String Function(const char* value)
		{
			return String('"') + String(value) + String('"');
		}
	};

	/** Implementation of 'ToString' for const c-strings */
	template <>
	struct ToString < const char* > final
	{
		FORCEINLINE static String Function(const char* value)
		{
			return String(value);
		}
	};

	/** Implementation of 'ToExplicitString' for const c-strings */
	template <>
	struct ToExplicitString < const char* > final
	{
		FORCEINLINE static String Function(const char* value)
		{
			return String('"') + String(value) + String('"');
		}
	};

	/** Implementation of 'ToString' for clang/gcc c-string literals */
	template <std::size_t size>
	struct ToString < char[size] > final
	{
		FORCEINLINE static String Function(const char value[size])
		{
			return String(value);
		}
	};

	/** Implementation of 'ToExplicitString' for clang/gcc c-string literals */
	template <std::size_t size>
	struct ToExplicitString < char[size] > final
	{
		FORCEINLINE static String Function(const char value[size])
		{
			return '"' + String(value) + '"';
		}
	};

	/** Implementation of 'ToString' for MSVC c-string literals */
	template <std::size_t size>
	struct ToString < const char[size] > final
	{
		FORCEINLINE static String Function(const char value[size])
		{
			return String(value);
		}
	};

	/** Implementation of 'ToExplicitString' for MSVC c-string literals @TODO: Determine if this can be removed */
	template <std::size_t size>
	struct ToExplicitString < const char[size] > final
	{
		FORCEINLINE static String Function(const char value[size])
		{
			return '"' + String(value) + '"';
		}
	};

	/** Implementation of 'ToString' for String */
	template <>
	struct ToString < String > final
	{
		FORCEINLINE static String Function(const String& value)
		{
			return value;
		}
	};

	/** Implementation of 'ToExplicitString' for 'String' */
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

	/** Implementation of 'ToString' for Array */
	template <typename T>
	struct ToString < Array<T> > final
	{
		FORCEINLINE static String Function(const Array<T>& value)
		{
			return ContainerToString<Array, T>::Function(value);
		}
	};

	/** Implementation of 'ToString' for List */
	template <typename T>
	struct ToString < List<T> > final
	{
		FORCEINLINE static String Function(const List<T>& value)
		{
			return ContainerToString<List, T>::Function(value);
		}
	};

	/** Implementation of 'ToString' for Queue */
	template <typename T>
	struct ToString < Queue<T> > final
	{
		FORCEINLINE static String Function(const Queue<T>& value)
		{
			return ContainerToString<Queue, T>::Function(value);
		}
	};

	/** Implementation of 'ToString' for Stack */
	template <typename T>
	struct ToString < Stack<T> > final
	{
		FORCEINLINE static String Function(const Stack<T>& value)
		{
			return ContainerToString<Stack, T>(value);
		}
	};

	/** Implementation of 'ToString' for Table */
	template <typename KeyT, typename ValueT>
	struct ToString < Table<KeyT, ValueT> > final
	{
		static String Function(const Table<KeyT, ValueT>& value)
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
					ToExplicitString<KeyT>::Function(pair.First),
					ToExplicitString<ValueT>::Function(pair.Second));
			}

			return result + '}';
		}
	};

	/** Implementation of 'ToString' for Pair */
	template <typename A, typename B>
	struct ToString < Pair<A, B> > final
	{
		FORCEINLINE static String Function(const Pair<A, B>& value)
		{
			return Format(
				"{@ | @}",
				ToExplicitString<A>::Function(value.First),
				ToExplicitString<B>::Function(value.Second));
		}
	};
}

/////////////////////
///   Functions   ///

/** Formats the state of the given value as a String.
* NOTE: The default behavior is to return the value's type name.
* You can override this behavior by implementing the 'String ToString() const' public member function,
* or by specializing the 'Implementation::ToString' struct. */
template <typename T>
FORCEINLINE String ToString(const T& value)
{
	return Implementation::ToString<T>::Function(value);
}

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
String Format(const String& format, const T& value, const MoreT& ... more)
{
	for (uint32 i = 0; i < format.Length(); ++i)
	{
		if (format[i] == '@')
		{
			return format.SubString(0, i) + ToString(value) + Format(format.SubString(i + 1), more...);
		}
	}

	// You passed in an empty format String, dumbass
	return "";
}

/** Experimental fast implementation of String formattig. This is pretty low-priority, but once I get the engine stuff worked out
* I'll come back and fix this. */
template <typename ... T>
String fFormat(const String& format, const T& ... values)
{
    // Turn our values into an array of Strings
    String strs[] = { ToString(values)... };
    
    // Determine how large our stack buffer for the resultant string must be
    uint32 bufferSize = (format.Length() + 1) * sizeof(Char);
    for (const auto& str : strs)
    {
        bufferSize += str.Length() * sizeof(Char);
    }
    
    // The start of our stack buffer for the string
    auto buffStart = (Char*)malloc(bufferSize);
    memset(buffStart, 0, bufferSize);
    auto buff = buffStart;
    
    // Iterate over the format string
    for (uint32 formatIndex = 0, valueIndex = 0; formatIndex < format.Length(); ++formatIndex)
    {
        // Get the current character from the format string
        Char c = format[formatIndex];
        
        // If we've reached a format character, and we have more value strings to add
        if (c == '@' && valueIndex < sizeof...(values))
        {
            const String& vString = strs[valueIndex];
            memcpy(buff, vString.Cstr(), vString.Length());
            
            buff += vString.Length();
            valueIndex++;
        }
        else
        {
            *buff = c;
            buff++;
        }
    }
    
    // Create string from result, and free buffer
    String result = buffStart;
    free(buffStart);
    return result;
}
