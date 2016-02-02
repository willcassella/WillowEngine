// Utility.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "TypeTraits.h"

namespace stde
{
	namespace Implementation
	{
		/** Executes the given function with the given arguments, since the predicate is true. */
		template <typename F, typename ... Args>
		void conditionally_execute(std::true_type /*predicate*/, F&& function, Args&& ... args)
		{
			std::forward<F>(function)(std::forward<Args>(args)...);
		}

		/** Does not execute the given function with the given arguments, since the predicate is false. */
		template <typename F, typename ... Args>
		void conditionally_execute(std::false_type /*predicate*/, F&& /*function*/, Args&& ... /*args*/)
		{
			// Do nothing
		}
	}

	/** Returns a reference to the given value as const. 
	* Note: 'std::as_const' is a proposal for C++17, so this should be deprecated once that rolls around. */
	template <typename T>
	const T& as_const(const T& value)
	{
		return value;
	}

	/** Not safe for rvalue-references. 
	* Note: 'std::as_const' is a proposal for C++17, so this should be deprecated once that rolls around. */
	template <typename T>
	const T& as_const(const T&& value) = delete;

	/** Executes the given function with the given arguments if the predicate is true, otherwise does nothing.
	* NOTE: This is a useful substitute for 'static_if', and should be deprecated once that becomes a part of the language. */
	template <bool Predicate, typename F, typename ... Args>
	void conditionally_execute(F&& function, Args&& ... args)
	{
		Implementation::conditionally_execute(bool_constant<Predicate>{}, std::forward<F>(function), std::forward<Args>(args)...);
	}
}
