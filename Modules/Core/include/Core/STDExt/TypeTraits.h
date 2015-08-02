// TypeTraits.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <type_traits>
#include "../Forwards/Core.h"

/////////////////
///   Types   ///

namespace stdEXT
{
	/** Evaluates to 'true' if the given type is a primitive (arithmetic, or pointer). */
	template <typename T>
	struct is_primitive
		: std::integral_constant<bool, std::is_arithmetic<T>::value || std::is_pointer<T>::value>
	{};

	/** Evaluates to 'true' if the given type is a reference to const. */
	template <typename T>
	struct is_const_reference
		: std::is_same<const std::decay_t<T>&, T>
	{};

	/** Evaluates to 'true' if the given type is a reference to non-const. */
	template <typename T>
	struct is_non_const_reference
		: std::is_same<std::decay_t<T>&, T>
	{};

	/** Evaluates to 'true' if the given type is an interface. */
	template <typename T>
	struct is_interface final
		: std::integral_constant<bool,
		std::is_base_of<Interface, T>::value &&
		!std::is_base_of<Object, T>::value &&
		std::is_abstract<T>::value &&
		sizeof(Interface) == sizeof(T)>
	{};

	/** Type holding a sequence of other types. */
	template <typename ... T>
	struct type_sequence final
	{};
}

//////////////////
///   Macros   ///

/** This macro makes std::enable_if a little easier on the eyes.
* It has to be a variadic macro, because otherwise the preprocessor interprets
* any commas in the template argument as separate macro arguments, and throws an error. 
* Unfortunately, Visual Studio's Intellisense has a hard time parsing this, and usually makes
* at least half of the argument uncolored. */
#define WHERE(...) typename = ::std::enable_if_t<__VA_ARGS__>
