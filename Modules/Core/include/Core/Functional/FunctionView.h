// FunctionView.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <utility>
#include "../Utility/View.h"

/** Allows lambdas to be passed down the stack without using templates or dynamic allocation. */
template <typename R, typename ... Args>
struct FunctionView final : View
{
	////////////////////////
	///   Constructors   ///
public:

	/** Creates a new FunctionView that calls 'func'. */
	template <typename F>
	FunctionView(F&& func)
	{
		_func = &func;
		_invoker = [](void* f, Args ... args) -> R
		{
			// So apparently if I do this within parentesis, Clang and GCC think that I'm referring to the overloaded operator().
			auto& ref = *static_cast<std::decay_t<F>*>(f);
			return ref(std::forward<Args>(args)...);
		};
	}

	/////////////////////
	///   Operators   ///
public:

	/** Invokes the held function. */
	R operator()(Args ... args)
	{
		return _invoker(_func, std::forward<Args>(args)...);
	}

	////////////////
	///   Data   ///
private:

	void* _func;
	R(*_invoker)(void*, Args...);
};
