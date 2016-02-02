// FromString.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Forwards/Operations.h"
#include "../Containers/String.h"

namespace Operations
{
	/** Generic implementation of 'FromString' */
	template <typename T>
	struct FromString final
	{
	private:

		/** Detects support for this operation if the 'String FromString(const String&)' member function is present. */
		template <typename F, typename ImplT = decltype(&F::FromString)>
		static constexpr bool HasSupport(Implementation::Preferred)
		{
			return std::is_convertible<ImplT, String(F::*)(const String&)>::value ||
				std::is_convertible<ImplT, String(F::*)(String)>::value;
		}

		/** Detects lack of support for this operation. */
		template <typename F>
		static constexpr bool HasSupport(Implementation::Fallback)
		{
			return false;
		}

	public:

		/** Executes the operation. */
		static void Function(String &out, T& value, const String& string)
		{
			out = value.FromString(string);
		}

		/** Whether this operation is supported for the given type. */
		static constexpr bool Supported = HasSupport<T>(0);
	};

	///////////////////////////
	///   Primitive Types   ///

	/** Implementation of 'FromString' for bool */
	template <>
	struct CORE_API FromString < bool > final
	{
		static void Function(String& out, bool& value, const String& string);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromString' for char */
	template <>
	struct CORE_API FromString < char > final
	{
		static void Function(String& out, char& value, const String& string);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromString' for byte */
	template <>
	struct CORE_API FromString < byte > final
	{
		static void Function(String& out, byte& value, const String& string);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromString' for int16 */
	template <>
	struct CORE_API FromString < int16 > final
	{
		static void Function(String& out, int16& value, const String& string);
		
		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromString' for int32 */
	template <>
	struct CORE_API FromString < int32 > final
	{
		static void Function(String& out, int32& value, const String& string);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromString' for int64 */
	template <>
	struct CORE_API FromString < int64 > final
	{
		static void Function(String& out, int64& value, const String& string);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromString' for uint16 */
	template <>
	struct CORE_API FromString < uint16 > final
	{
		static void Function(String& out, uint16& value, const String& string);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromString' for uint32 */
	template <>
	struct CORE_API FromString < uint32 > final
	{
		static void Function(String& out, uint32& value, const String& string);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromString' for uint64 */
	template <>
	struct CORE_API FromString < uint64 > final
	{
		static void Function(String& out, uint64& value, const String& string);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromString' for float */
	template <>
	struct CORE_API FromString < float > final
	{
		static void Function(String& out, float& value, const String& string);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromString' for double */
	template <>
	struct CORE_API FromString < double > final
	{
		static void Function(String& out, double& value, const String& string);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromString' for long double */
	template <>
	struct CORE_API FromString < long double > final
	{
		static void Function(String& out, long double& value, const String& string);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromString' for pointers */
	template <typename T>
	struct FromString < T* > final
	{
		static void Function(String& out, T*& value, const String& string)
		{
			if (string.StartsWith("0x"))
			{
				value = nullptr;
				out = string.SubString(9); // @TODO: Implement this
			}
			else
			{
				value = nullptr;
				out = string;
			}
		}

		static constexpr bool Supported = true;
	};

	////////////////////////
	///   String Types   ///

	/** Implementation of 'FromString' for String */
	template <>
	struct CORE_API FromString < String > final
	{
		static void Function(String& out, String& value, const String& string);

		static constexpr bool Supported = true;
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
	static_assert(Operations::FromString<T>::Supported,
		"'FromString' is not supported on the given type. If it's supposed to be, make sure the member function signature is correct.");

	String out;
	Operations::FromString<T>::Function(out, value, string);
	return out;
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
