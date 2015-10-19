// TypeTraits.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <type_traits>

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
	
	/** Evaluates to 'true' if the given type is a const object. */
	template <typename T>
	struct is_const_object
		: std::integral_constant<bool, std::is_object<T>::value && std::is_const<T>::value>
	{};
	
	/** Evaluates to 'true' if the given type is a non-const object. */
	template <typename T>
	struct is_non_const_object
		: std::integral_constant<bool, std::is_object<T>::value && !std::is_const<T>::value>
	{};

	/** Evaluates to 'true' if the given type (T) implements the given contract (ContractT). */
	template <class T, template <class F> class ContractT>
	struct has_contract
		: std::is_base_of<ContractT<T>, T>
	{};

	/** Type holding a sequence of other types. */
	template <typename ... T>
	struct type_sequence final
	{
		/** Returns whether this type_sequence contains the given type. */
		template <typename S>
		static constexpr bool Contains()
		{
			return Contains<S>(type_sequence<T...>{});
		}

	private:

		/** Recursively checks each element of the given type_sequence. */
		template <typename S, typename C, typename ... F>
		static constexpr bool Contains(type_sequence<C, F...>)
		{
			return std::is_same<S, C>::value || Contains<S>(type_sequence<F...>{});
		}

		/** Case were we have no more types in the type_sequence. */
		template <typename S>
		static constexpr bool Contains(type_sequence<>)
		{
			return false;
		}
	};
}

//////////////////
///   Macros   ///

/** This macro makes std::enable_if a little easier on the eyes.
* It has to be a variadic macro, because otherwise the preprocessor interprets
* any commas in the template argument as separate macro arguments, and throws an error. 
* Unfortunately, Visual Studio's Intellisense has a hard time parsing this, and usually makes
* at least half of the argument uncolored. */
#define WHERE(...) typename = ::std::enable_if_t<__VA_ARGS__>
