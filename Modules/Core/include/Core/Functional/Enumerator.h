// Enumerator.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <utility>
#include <type_traits>
#include "../Utility/View.h"

enum class EnumeratorControl
{
	/** Continues the enumeration. */
	Continue,
	
	/** Quits the enumeration. */
	Break
};

template <typename T>
struct Enumerator final : View
{
	////////////////////////
	///   Constructors   ///
public:

	template <typename F>
	Enumerator(F&& func)
	{
		Setup(func);
	}

    Enumerator(Enumerator&& move) = default;
	Enumerator(Enumerator& copy)
        : View(copy), _func(copy._func), _invoker(copy._invoker)
    {
        // I have to define this because apparently MSVC can't deal with having multiple defaulted copy-constructors.
    }
	Enumerator(const Enumerator& copy)
		: View(copy), _func(copy._func), _invoker(copy._invoker)
	{
		// I have to define this because apparently MSVC can't deal with having multiple defaulted copy-constructors.
	}

	///////////////////
	///   Methods   ///
private:

	/** Creates an invoker that decides whether to continue or not. */
	template <typename F>
	auto Setup(F&& func) -> std::enable_if_t<std::is_same<EnumeratorControl, std::result_of_t<F(T)>>::value>
	{
		_func = &func;
		_invoker = [](void* f, T value) -> EnumeratorControl
		{
			return (*static_cast<std::decay_t<F>*>(f))(std::forward<T>(value));
		};
	}

	/** Creates an invoker that always continues. */
	template <typename F>
	auto Setup(F&& func) -> std::enable_if_t<std::is_void<std::result_of_t<F(T)>>::value>
	{
		_func = &func;
		_invoker = [](void* f, T value) -> EnumeratorControl
		{
			(*static_cast<std::decay_t<F>*>(f))(std::forward<T>(value));
			return EnumeratorControl::Continue;
		};
	}

	/////////////////////
	///   Operators   ///
public:

	/** Enumerates over the given enumerable object. */
	template <typename E>
	void operator()(E&& enumerable)
	{
		for (T i : enumerable)
		{
			auto result = _invoker(_func, std::forward<T>(i));

			if (result == EnumeratorControl::Break)
			{
				break;
			}
		}
	}

	////////////////
	///   Data   ///
private:

	void* _func;
	EnumeratorControl(*_invoker)(void*, T);
};
