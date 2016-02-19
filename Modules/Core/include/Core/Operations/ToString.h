// ToString.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <cstdlib>
#include <cstring>
#include "../Umbrellas/Containers.h"

namespace Operations
{
	/** Generic implementation of 'ToString' */
	template <typename T>
	struct ToString final
	{
	private:

		/** Detects support for this operation if the 'String ToString() const' member function is present. */
		template <typename F, typename ImplT = decltype(&F::ToString)>
		static constexpr bool HasSupport(Implementation::Preferred)
		{
			return std::is_convertible<ImplT, String(F::*)() const>::value ||
				std::is_convertible<ImplT, const String& (F::*)() const>::value;
		}

		/** Detects lack of support for this operation. */
		template <typename F>
		static constexpr bool HasSupport(Implementation::Fallback)
		{
			return false;
		}

	public:

		/** Executes the operation. */
		static void Function(String& out, const T& value)
		{
			out = value.ToString();
		}

		/** Whether this operation is supported for the given type. */
		static constexpr bool Supported = HasSupport<T>(0);
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
		static void Function(String& out, bool value);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToString' for char */
	template <>
	struct CORE_API ToString < char > final
	{
		static void Function(String& out, char value);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToString' for byte */
	template <>
	struct CORE_API ToString < byte > final
	{
		static void Function(String& out, byte value);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToString' for int16 */
	template <>
	struct CORE_API ToString < int16 > final
	{
		static void Function(String& out, int16 value);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToString' for uint16 */
	template <>
	struct CORE_API ToString < uint16 > final
	{
		static void Function(String& out, uint16 value);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToString' for int32 */
	template <>
	struct CORE_API ToString < int32 > final
	{
		static void Function(String& out, int32 value);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToString' for uint32 */
	template <>
	struct CORE_API ToString < uint32 > final
	{
		static void Function(String& out, uint32 value);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToString' for int64 */
	template <>
	struct CORE_API ToString < int64 > final
	{
		static void Function(String& out, int64 value);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToString' for uint64 */
	template <>
	struct CORE_API ToString < uint64 > final
	{
		static void Function(String& out, uint64 value);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToString' for float */
	template <>
	struct CORE_API ToString < float > final
	{
		static void Function(String& out, float value);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToString' for double */
	template <>
	struct CORE_API ToString < double > final
	{
		static void Function(String& out, double value);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToString' for long double */
	template <>
	struct CORE_API ToString < long double > final
	{
		static void Function(String& out, long double value);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToString' for pointers */
	template <typename T>
	struct ToString < T* > final
	{
		FORCEINLINE static void Function(String& out, T* /*value*/)
		{
			out = "0xAddress"; // @TODO: Implement this
		}

		static constexpr bool Supported = true;
	};

	////////////////////////
	///   String Types   ///

	/** Implementation of 'ToString' for non-const c-strings */
	template <>
	struct ToString < char* > final
	{
		FORCEINLINE static void Function(String& out, const char* value)
		{
			out = value;
		}

		static constexpr bool Supported = true;
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
		FORCEINLINE static void Function(String& out, const char* value)
		{
			out = value;
		}

		static constexpr bool Supported = true;
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
		FORCEINLINE static void Function(String& out, const char value[size])
		{
			out = value;
		}

		static constexpr bool Supported = true;
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
		FORCEINLINE static void Function(String& out, const char value[size])
		{
			out = value;
		}

		static constexpr bool Supported = true;
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
		FORCEINLINE static void Function(String& out, const String& value)
		{
			out = value;
		}

		static constexpr bool Supported = true;
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
		static void Function(String& out, const Array<T>& value)
		{
			out = ContainerToString<Array, T>::Function(value);
		}

		static constexpr bool Supported = ToString<T>::Supported;
	};

	/** Implementation of 'ToString' for List */
	template <typename T>
	struct ToString < List<T> > final
	{
		static void Function(String& out, const List<T>& value)
		{
			out = ContainerToString<List, T>::Function(value);
		}

		static constexpr bool Supported = ToString<T>::Supported;
	};

	/** Implementation of 'ToString' for Queue */
	template <typename T>
	struct ToString < Queue<T> > final
	{
		static void Function(String& out, const Queue<T>& value)
		{
			out = ContainerToString<Queue, T>::Function(value);
		}

		static constexpr bool Supported = ToString<T>::Supported;
	};

	/** Implementation of 'ToString' for Stack */
	template <typename T>
	struct ToString < Stack<T> > final
	{
		static void Function(String& out, const Stack<T>& value)
		{
			out = ContainerToString<Stack, T>(value);
		}

		static constexpr bool Supported = ToString<T>::Supported;
	};

	/** Implementation of 'ToString' for Table */
	template <typename KeyT, typename ValueT>
	struct ToString < Table<KeyT, ValueT> > final
	{
		static void Function(String& out, const Table<KeyT, ValueT>& value)
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

			out = result + '}';
		}

		static constexpr bool Supported = ToString<KeyT>::Supported && ToString<ValueT>::Supported;
	};

	/** Implementation of 'ToString' for Pair */
	template <typename A, typename B>
	struct ToString < Pair<A, B> > final
	{
		static void Function(String& out, const Pair<A, B>& value)
		{
			out = Format(
				"{@ | @}",
				ToExplicitString<A>::Function(value.First),
				ToExplicitString<B>::Function(value.Second));
		}

		static constexpr bool Supported = ToString<A>::Supported && ToString<B>::Supported;
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
	static_assert(Operations::ToString<T>::Supported,
		"'ToString' is not supported on the given type. If it's supposed to be, make sure the member function signature is correct.");

	String out;
	Operations::ToString<T>::Function(out, value);
	return out;
}

/** Formats the given String with the given value, returning the result
* - The first instance of the '@' character in 'format' is replaced with a String representation of 'value' */
template <typename T>
String Format(const String& format, const T& value)
{
	for (std::size_t i = 0; i < format.Length(); ++i)
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
	for (std::size_t i = 0; i < format.Length(); ++i)
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
    auto bufferSize = format.Length() + 1;
    for (const auto& str : strs)
    {
        bufferSize += str.Length();
    }
    
    // The start of our stack buffer for the string
    auto buffStart = static_cast<Char*>(std::calloc(bufferSize, sizeof(Char)));
    auto buff = buffStart;
    
    // Iterate over the format string
    for (std::size_t formatIndex = 0, valueIndex = 0; formatIndex < format.Length(); ++formatIndex)
    {
        // Get the current character from the format string
        Char c = format[formatIndex];
        
        // If we've reached a format character, and we have more value strings to add
        if (c == '@' && valueIndex < sizeof...(values))
        {
            const String& vString = strs[valueIndex];
            std::memcpy(buff, vString.Cstr(), vString.Length());
            
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
    String result(buffStart);
    std::free(buffStart);
    return result;
}
