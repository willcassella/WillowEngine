// FunctionView.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <utility>

/** Allows lambdas to be passed down the stack without using templates or dynamic allocation. */
template <typename R, typename ... Args>
struct FunctionView final
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
			return (*static_cast<std::decay_t<F>*>(f))(std::forward<Args>(args)...);
		};
	}

	FunctionView(FunctionView& copy)
		: _func(copy._func), _invoker(copy._invoker)
	{
		// All done TODO: Default this once MSVC doesn't suck
	}
	FunctionView(const FunctionView& copy)
		: _func(copy._func), _invoker(copy._invoker)
	{
		// All done TODO: Default this once MSVC doesn't suck
	}
	FunctionView(FunctionView&& move) = default;

	/////////////////////
	///   Operators   ///
public:

	/** Invokes the held function. */
	R operator()(Args ... args) const
	{
		return _invoker(_func, std::forward<Args>(args)...);
	}

	////////////////
	///   Data   ///
private:

	void* _func;
	R(*_invoker)(void*, Args...);
};
