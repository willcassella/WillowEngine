// TypeTraits.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <type_traits>

namespace stdEXT
{
	namespace Implementation
	{
		/** Executes the given function with the given arguments, since the predicate is true. */
		template <typename T, typename ... Args>
		void conditionally_execute(std::true_type /*predicate*/, const T& function, Args&& ... args)
		{
			function(std::forward<Args>(args)...);
		}

		/** Does not execute the given function with the given arguments, since the predicate is false. */
		template <typename T, typename ... Args>
		void conditionally_execute(std::false_type /*predicate*/, const T& /*function*/, Args&& ... /*args*/)
		{
			// Do nothing
		}
	}

	/////////////////
	///   Types   ///

	/** Type representing boolean constants.
	* NOTE: This should be removed in favor of 'std::bool_constant' once C++17 rolls around. */
	template <bool Value>
	using bool_constant = std::integral_constant<bool, Value>;

	//////////////////
	///   Traits   ///

	/** Evaluates to 'true' if the given type is a primitive (arithmetic, or pointer). */
	template <typename T>
	using is_primitive = bool_constant<std::is_arithmetic<T>::value || std::is_pointer<T>::value>;

	/** Evaluates to 'true' if the given type is a reference to const. */
	template <typename T>
	using is_const_reference = std::is_same<const std::decay_t<T>&, T>;

	/** Evaluates to 'true' if the given type is a reference to non-const. */
	template <typename T>
	using is_mutable_reference = std::is_same<std::decay_t<T>&, T>;

	/** Evaluates to 'true' if the given type is a const object. */
	template <typename T>
	using is_const_object = bool_constant<std::is_object<T>::value && std::is_const<T>::value>;

	/** Evaluates to 'true' if the given type is a non-const object. */
	template <typename T>
	using is_mutable_object = bool_constant<std::is_object<T>::value && !std::is_const<T>::value>;

	/** Evaluates to 'true' if the given type (T) implements the given contract (ContractT). */
	template <class T, template <class F> class ContractT>
	using has_contract = std::is_base_of<ContractT<T>, T>;

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

	/////////////////////
	///   Functions   ///

	/** Executes the given function with the given arguments if the predicate is true, otherwise does nothing. 
	* NOTE: This is a useful substitute for 'static_if', and should be deprecated once that becomes a part of the language. */
	template <bool Predicate, typename T, typename ... Args>
	void conditionally_execute(const T& function, Args&& ... args)
	{
		Implementation::conditionally_execute(bool_constant<Predicate>{}, function, std::forward<Args>(args)...);
	}
}

//////////////////
///   Macros   ///

/** This macro makes std::enable_if a little easier on the eyes.
* It has to be a variadic macro, because otherwise the preprocessor interprets
* any commas in the template argument as separate macro arguments, and throws an error.
* Unfortunately, Visual Studio's Intellisense has a hard time parsing this, and usually makes
* at least half of the argument uncolored. */
#define WHERE(...) typename = ::std::enable_if_t<__VA_ARGS__>
