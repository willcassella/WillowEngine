// TypeOps.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <type_traits>
#include "../config.h"

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Conditionally constructs a type, returning whether it was successful. */
	template <typename T, typename ... Args>
	struct Construct final
	{
	private:

		/** Implementation for if the type IS constructible. */
		template <typename F>
		FORCEINLINE static void Impl(std::true_type, byte* location, Args ... args)
		{
			new (location) F(std::forward<Args>(args)...);
		}

		/** Implementation for if the type IS NOT constructible. */
		template <typename F>
		FORCEINLINE static void Impl(std::false_type, byte* /*location*/, Args ... /*args*/)
		{
			// Do nothing
		}

	public:

		/** Entry point for the implementation. */
		FORCEINLINE static void Function(byte* location, Args ... args)
		{
			Impl<T>(std::integral_constant<bool, Result>(), location, std::forward<Args>(args)...);
		}

		/** Whether the type is constructible with these arguments. */
		static constexpr bool Result = std::is_constructible<T, Args...>::value;
	};

	// TODO: Documentation
	template <typename T, typename Arg>
	struct Assign final
	{
	private:

		/** Implementation for if the type IS assignable. */
		template <typename F>
		FORCEINLINE static void Impl(std::true_type, F& value, Arg arg)
		{
			value = std::forward<Arg>(arg);
		}

		/** Implementation for if the type IS NOT assignable. */
		template <typename F>
		FORCEINLINE static void Impl(std::false_type, F& /*value*/, Arg /*arg*/)
		{
			// Do nothing
		}

	public:

		/** Entry point for the implementation. */
		FORCEINLINE static void Function(T& value, Arg arg)
		{
			Impl(std::integral_constant<bool, Result>(), value, std::forward<Arg>(arg));
		}

		/** Whether the implementation succeeds in assigning to the object. */
		static constexpr bool Result = std::is_assignable<T, Arg>::value;
	};

	// TODO: Documentation
	template <typename T>
	struct Destroy final
	{
	private:

		/** Implementation for if the type IS destructible. */
		template <typename F>
		FORCEINLINE static void Impl(std::true_type, F& value)
		{
			value.~F();
		}

		/** Implementation for if the type IS NOT destructible. */
		template <typename F>
		FORCEINLINE static void Impl(std::false_type, F& /*value*/)
		{
			// Do nothing
		}

	public:

		/** Entry point for the implementation. */
		FORCEINLINE static void Function(T& value)
		{
			Impl(std::integral_constant<bool, Result>(), value);
		}

		/** Whether the implementation succeeds in destroying the object. */
		static constexpr bool Result = std::is_destructible<T>::value;
	};
}
