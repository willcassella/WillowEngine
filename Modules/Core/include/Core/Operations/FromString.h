// FromString.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Forwards/Operations.h"
#include "../String.h"

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Generic implementation of 'FromString' */
	template <typename T>
	struct FromString final
	{
	private:

		/** Implementation for if the type defines its own 'FromString' method (preferred). */
		template <typename F>
		FORCEINLINE static auto Impl(Preferred, F& value, const String& string) -> decltype(value.F::FromString(string))
		{
			return value.FromString(string);
		}

		/** Implementation for if the type does not define its own 'FromString' method (fallback). */
		template <typename F>
		FORCEINLINE static auto Impl(Fallback, F& value, const String& string) -> String
		{
			return Default::FromString(value, string);
		}

	public:

		/** Entry point for the implementation. */
		FORCEINLINE static String Function(T& value, const String& string)
		{
			using ReturnType = decltype(Impl(0, value, string));
			static_assert(std::is_same<String, ReturnType>::value || std::is_same<const String&, ReturnType>::value,
				"The return type of the 'FromString' method must either be a 'String' or a const reference to one.");

			return Impl(0, value, string);
		}
	};

	///////////////////////////
	///   Primitive Types   ///

	/** Implementation of 'FromString' for bool */
	template <>
	struct CORE_API FromString < bool > final
	{
		static String Function(bool& value, const String& string);
	};

	/** Implementation of 'FromString' for char */
	template <>
	struct CORE_API FromString < char > final
	{
		static String Function(char& value, const String& string);
	};

	/** Implementation of 'FromString' for byte */
	template <>
	struct CORE_API FromString < byte > final
	{
		static String Function(byte& value, const String& string);
	};

	/** Implementation of 'FromString' for int16 */
	template <>
	struct CORE_API FromString < int16 > final
	{
		static String Function(int16& value, const String& string);
	};

	/** Implementation of 'FromString' for int32 */
	template <>
	struct CORE_API FromString < int32 > final
	{
		static String Function(int32& value, const String& string);
	};

	/** Implementation of 'FromString' for int64 */
	template <>
	struct CORE_API FromString < int64 > final
	{
		static String Function(int64& value, const String& string);
	};

	/** Implementation of 'FromString' for uint16 */
	template <>
	struct CORE_API FromString < uint16 > final
	{
		static String Function(uint16& value, const String& string);
	};

	/** Implementation of 'FromString' for uint32 */
	template <>
	struct CORE_API FromString < uint32 > final
	{
		static String Function(uint32& value, const String& string);
	};

	/** Implementation of 'FromString' for uint64 */
	template <>
	struct CORE_API FromString < uint64 > final
	{
		static String Function(uint64& value, const String& string);
	};

	/** Implementation of 'FromString' for float */
	template <>
	struct CORE_API FromString < float > final
	{
		static String Function(float& value, const String& string);
	};

	/** Implementation of 'FromString' for double */
	template <>
	struct CORE_API FromString < double > final
	{
		static String Function(double& value, const String& string);
	};

	/** Implementation of 'FromString' for pointers */
	template <typename T>
	struct FromString < T* > final
	{
		static String Function(T*& value, const String& string)
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

	/** Implementation of 'FromString' for String */
	template <>
	struct CORE_API FromString < String > final
	{
		static String Function(String& value, const String& string);
	};
}

/////////////////////
///   Functions   ///

/** Sets the state of the given value by parsing a String, returning the remainder of the String.
* NOTE: The default behavior is to not modify the value and return the String as is.
* You can override this behavior by implementing the 'String FromString(const String& string)' public member function,
* or by specializing the 'Implementation::FromString' struct. */
template <typename T>
FORCEINLINE String FromString(T& value, const String& string)
{
	return Implementation::FromString<T>::Function(value, string);
}

/** Parses the given value from the given String, following the given format. The remainder of the String is returned.
* - The location of the '@' character in the format String denotes the location of the value in the given String */
template <typename T>
String Parse(const String& string, const String& format, T& value)
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
String Parse(const String& string, const String& format, T& value, MoreT& ... moreValues)
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
