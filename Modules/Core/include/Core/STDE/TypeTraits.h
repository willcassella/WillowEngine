// TypeTraits.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <utility>
#include <type_traits>

namespace stde
{
	/////////////////
	///   Types   ///

	/** Type representing boolean constants.
	* NOTE: This should be removed in favor of 'std::bool_constant' once C++17 rolls around. */
	template <bool Value>
	using bool_constant = std::integral_constant<bool, Value>;

	/** Type holding a sequence of other types. */
	template <typename ... T>
	struct type_sequence final
	{
		/** Returns whether this type_sequence contains the given type. */
		template <typename S>
		static constexpr bool contains()
		{
			return type_sequence::contains<S>(type_sequence<T...>{});
		}

	private:

		/** Recursively checks each element of the given type_sequence. */
		template <typename S, typename C, typename ... F>
		static constexpr bool contains(type_sequence<C, F...>)
		{
			return std::is_same<S, C>::value || type_sequence::contains<S>(type_sequence<F...>{});
		}

		/** Case were we have no more types in the type_sequence. */
		template <typename S>
		static constexpr bool contains(type_sequence<>)
		{
			return false;
		}
	};

	//////////////////
	///   Traits   ///

	/** Evaluates to 'true' if the given type is a primitive (arithmetic, pointer, or enum). */
	template <typename T>
	using is_primitive = bool_constant<std::is_arithmetic<T>::value || std::is_pointer<T>::value || std::is_enum<T>::value>;

	/** Evaluates to 'true' if the given type is not const. */
	template <typename T>
	using is_mutable = bool_constant<std::is_object<T>::value && !std::is_const<T>::value>;

	/** Evaluates to 'true' if the given type is a reference to const. */
	template <typename T>
	using is_reference_to_const = bool_constant<std::is_reference<T>::value && std::is_const<std::remove_reference_t<T>>::value>;

	/** Evaluates to 'true' if the given type is a reference to non-const. */
	template <typename T>
	using is_reference_to_mutable = bool_constant<std::is_reference<T>::value && is_mutable<std::remove_reference_t<T>>::value>;

	/** Evaluates to 'true' if the given type is const, or a reference to const. */
	template <typename T>
	using has_const = bool_constant<std::is_const<T>::value || is_reference_to_const<T>::value>;

	/** Evaluates to 'true' if the given type is mutable, or a reference to mutable. */
	template <typename T>
	using has_mutable = bool_constant<is_mutable<T>::value || is_reference_to_mutable<T>::value>;

	///////////////////////////
	///   Transformations   ///

	/** Removes the r-value reference qualifier from a type, decaying it to an lvalue-rference or an object. */
	template <typename T>
	struct remove_rvalue_reference final
	{
		using type = T;
	};

	/** Removes the r-value reference qualifier from a type, decaying it to an lvalue-rference or an object. */
	template <typename T>
	struct remove_rvalue_reference < T&& > final
	{
		using type = T&;
	};
	
	/** Removes the r-value reference qualifier from a type, decaying it to an lvalue-rference or an object. */
	template <typename T>
	using remove_rvalue_reference_t = typename remove_rvalue_reference<T>::type;

	/** Copies const qualifier from 'From' to 'To'. */
	template <typename From, typename To>
	struct copy_const final
	{
		using type = std::remove_const_t<To>;
	};

	/** Copies const qualifier from 'From' to 'In'. */
	template <typename From, typename To>
	struct copy_const < const From, To > final
	{
		using type = std::add_const_t<To>;
	};

	/** Copies const qualifier from 'From' to 'In'. */
	template <typename From, typename To>
	struct copy_const < const From&, To > final
	{
		using type = std::add_const_t<To>;
	};

	/** Copies const qualifier from 'From' to 'In'. */
	template <typename From, typename To>
	struct copy_const < const From&&, To > final
	{
		using type = std::add_const_t<To>;
	};

	/** Copies const qualifier from 'From' to 'To'. */
	template <typename From, typename To>
	using copy_const_t = typename copy_const<From, To>::type;

	/** Copies volatile qualifier from 'From' to 'To'. */
	template <typename From, typename To>
	struct copy_volatile final
	{
		using type = std::remove_volatile_t<To>;
	};

	/** Copies const qualifier from 'From' to 'To'. */
	template <typename From, typename To>
	struct copy_volatile < volatile From, To > final
	{
		using type = std::add_volatile_t<To>;
	};

	/** Copies const qualifier from 'From' to 'To'. */
	template <typename From, typename To>
	using copy_volatile_t = typename copy_volatile<From, To>::type;

	/** Copies const/volatile qualifiers from 'From' to 'To' */
	template <typename From, typename To>
	struct copy_cv final
	{
		using type = copy_const_t<From, copy_volatile_t<From, To>>;
	};

	/** Copies const/volatile qualifiers from 'From' to 'To'. */
	template <typename From, typename To>
	using copy_cv_t = typename copy_cv<From, To>::type;

	/** Copies lvalue/rvalue ref qualifiers from 'From' to 'To'. */
	template <typename From, typename To>
	struct copy_ref final
	{
		using type = std::remove_reference_t<To>;
	};

	/** Copies lvalue/rvalue ref qualifiers from 'From' to 'To'. */
	template <typename From, typename To>
	struct copy_ref < From&, To > final
	{
		using type = std::add_lvalue_reference_t<To>;
	};

	/** Copies lvalue/rvalue ref qualifiers from 'From' to 'To'. */
	template <typename From, typename To>
	struct copy_ref < From&&, To > final
	{
		using type = std::add_rvalue_reference_t<To>;
	};

	/** Copies lvalue/rvalue ref qualifiers from 'From' to 'To'. */
	template <typename From, typename To>
	using copy_ref_t = typename copy_ref<From, To>::type;

	/** Copies all cv/ref qualifiers from 'From' to 'To'. */
	template <typename From, typename To>
	struct copy_qualifiers final
	{
		using type = copy_ref_t<From, copy_cv_t<From, To>>;
	};

	/** Copies all cv/ref qualifiers from 'From' to 'To'. */
	template <typename From, typename To>
	using copy_qualifiers_t = typename copy_qualifiers<From, To>::type;

	/** Makes 'T' at least as const as 'Min'. */
	template <typename Min, typename T>
	struct minimum_const final
	{
		using type = T;
	};

	/** Makes 'T' at least as const as 'Min'. */
	template <typename Min, typename T>
	struct minimum_const < const Min, T >
	{
		using type = std::add_const_t<T>;
	};

	/** Makes 'T' at least as const as 'Min'. */
	template <typename Min, typename T>
	using minimum_const_t = typename minimum_const<Min, T>::type;

	/** Makes 'T' at least as volatile as 'Min'. */
	template <typename Min, typename T>
	struct minimum_volatile final
	{
		using type = T;
	};

	/** Makes 'T' at least as volatile as 'Min'. */
	template <typename Min, typename T>
	struct minimum_volatile < volatile Min, T > final
	{
		using type = std::add_volatile_t<T>;
	};

	/** Makes 'T' at least as const as 'Min'. */
	template <typename Min, typename T>
	using minimum_volatile_t = typename minimum_volatile<Min, T>::type;

	/** Makes 'T' at least as const/volatile as 'Min'. */
	template <typename Min, typename T>
	struct minimum_cv final
	{
		using type = minimum_const_t<Min, minimum_volatile_t<Min, T>>;
	};

	/** Makes 'T' at least as const/volatile as 'Min'. */
	template <typename Min, typename T>
	using minimum_cv_t = typename minimum_cv<Min, T>::type;

	/** Gives 'T' at least as many ref-qualifiers as 'Min'. */
	template <typename Min, typename T>
	struct minimum_ref final
	{
		using type = T;
	};

	/** Gives 'T' at least as many ref-qualifiers as 'Min'. */
	template <typename Min, typename T>
	struct minimum_ref < Min&, T > final
	{
		using type = std::add_lvalue_reference_t<T>;
	};

	/** Gives 'T' at least as many ref-qualifiers as 'Min'. */
	template <typename Min, typename T>
	struct minimum_ref < Min&&, T > final
	{
		using type = std::add_rvalue_reference_t<T>;
	};

	/** Gives 'T' at least as many ref-qualifiers as 'Min'. */
	template <typename Min, typename T>
	using minimum_ref_t = typename minimum_ref<Min, T>::type;

	/** Gives 'T' at least as many cv/ref qualifiers as 'Min'. */
	template <typename Min, typename T>
	struct minimum_qualifiers final
	{
		using type = minimum_ref_t<Min, minimum_cv_t<Min, T>>;
	};

	/** Gives 'T' at least as many cv/ref qualifiers as 'Min'. */
	template <typename Min, typename T>
	using minimum_qualifiers_t = typename minimum_qualifiers<Min, T>::type;

	/** Makes 'T' at most as const as 'Max'. */
	template <typename Max, typename T>
	struct maximum_const final
	{
		using type = std::remove_const_t<T>;
	};

	/** Makes 'T' at most as const as 'Max'. */
	template <typename Max, typename T>
	struct maximum_const < const Max, T > final
	{
		using type = T;
	};

	/** Makes 'T' at most as const as 'Max'. */
	template <typename Max, typename T>
	using maximum_const_t = typename maximum_const<Max, T>::type;

	/** Makes 'T' at most as volatile as 'Max'. */
	template <typename Max, typename T>
	struct maximum_volatile final
	{
		using type = std::remove_volatile_t<T>;
	};

	/** Makes 'T' at most as volatile as 'Max'. */
	template <typename Max, typename T>
	struct maximum_volatile < volatile Max, T > final
	{
		using type = T;
	};

	/** Makes 'T' at most as volatile as 'Max'. */
	template <typename Max, typename T>
	using maximum_volatile_t = typename maximum_volatile<Max, T>::type;

	/** Makes 'T' at most as const/volatile as 'Max'. */
	template <typename Max, typename T>
	struct maximum_cv final
	{
		using type = maximum_const_t<Max, maximum_volatile_t<Max, T>>;
	};

	/** Makes 'T' at most as const/volatile as 'Max'. */
	template <typename Max, typename T>
	using maximum_cv_t = typename maximum_cv<Max, T>::type;

	/** Gives 'T' at most as many ref-qualifiers as 'Max'. */
	template <typename Max, typename T>
	struct maximum_ref final
	{
		using type = std::remove_reference_t<T>;
	};

	/** Gives 'T' at most as many ref-qualifiers as 'Max'. */
	template <typename Max, typename T>
	struct maximum_ref < Max&, T > final
	{
		using type = remove_rvalue_reference_t<T>;
	};

	/** Gives 'T' at most as many ref-qualifiers as 'Max'. */
	template <typename Max, typename T>
	struct maximum_ref < Max&&, T > final
	{
		using type = T;
	};

	/** Gives 'T' at most as many ref-qualifiers as 'Max'. */
	template <typename Max, typename T>
	using maximum_ref_t = typename maximum_ref<Max, T>::type;
	
	/** Gives 'T' at most as many ref-qualifiers as 'Max'. */
	template <typename Max, typename T>
	struct maximum_qualifiers final
	{
		using type = maximum_ref_t<Max, maximum_cv_t<Max, T>>;
	};

	/** Gives 'T' at most as many ref-qualifiers as 'Max'. */
	template <typename Max, typename T>
	using maximum_qualifiers_t = typename maximum_qualifiers<Max, T>::type;

	/////////////////////
	///   Functions   ///

	namespace meta
	{
		/** Returns 'true' if all boolean constants in the given sequence are true. 
		* NOTE: This should be deprecated once fold expressions become a thing. */
		template <bool First>
		constexpr bool and(std::integer_sequence<bool, First>)
		{
			return First;
		}

		/** Returns 'true' if all boolean constants in the given sequence are true.
		* NOTE: This should be deprecated once fold expressions become a thing. */
		template <bool First, bool Second, bool ... Rest>
		constexpr bool and(std::integer_sequence<bool, First, Second, Rest...>)
		{
			return First && meta::and(std::integer_sequence<bool, Second, Rest...>());
		}

		/** Returns 'true' if all boolean constants in the given sequence are true.
		* NOTE: This should be deprecated once fold expressions become a thing. */
		template <bool First, bool ... Rest>
		constexpr bool and()
		{
			return meta::and(std::integer_sequence<bool, First, Rest...>());
		}

		/** Returns 'true' if any of the boolean constants in the given sequence are true.
		* NOTE: This should be deprecated once fold expressions become a thing. */
		template <bool First>
		constexpr bool or(std::integer_sequence<bool, First>)
		{
			return First;
		}

		/** Returns 'true' if any of the boolean constants in the given sequence are true.
		* NOTE: This should be deprecated once fold expressions become a thing. */
		template <bool First, bool Second, bool ... Rest>
		constexpr bool or(std::integer_sequence<bool, First, Second, Rest...>)
		{
			return First || meta::or(std::integer_sequence<bool, Second, Rest...>());
		}

		/** Returns 'true' if any of the boolean constants in the given sequence are true.
		* NOTE: This should be deprecated once fold expressions become a thing. */
		template <bool First, bool ... Rest>
		constexpr bool or()
		{
			return meta::or(std::integer_sequence<bool, First, Rest...>());
		}
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
