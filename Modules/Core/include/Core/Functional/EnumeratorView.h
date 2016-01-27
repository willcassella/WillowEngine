// EnumeratorView.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
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
struct EnumeratorView final : View
{
	////////////////////////
	///   Constructors   ///
public:

	template <typename F>
	EnumeratorView(F&& func)
		: _hasBroken(false)
	{
		Setup(func);
	}

    	EnumeratorView(EnumeratorView&& move) = default;
	EnumeratorView(EnumeratorView& copy)
        	: View(copy), _hasBroken(copy._hasBroken), _func(copy._func), _invoker(copy._invoker)
    	{
        	// I have to define this because apparently MSVC can't deal with having multiple defaulted copy-constructors.
    	}
	EnumeratorView(const EnumeratorView& copy)
		: View(copy), _hasBroken(copy._hasBroken), _func(copy._func), _invoker(copy._invoker)
	{
		// I have to define this because apparently MSVC can't deal with having multiple defaulted copy-constructors.
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether the enumerator has broken. If it has this EnumeratorView will refuse to continue enumeration,
	* but checking this can save you the trouble of trying. */
	FORCEINLINE bool HasBroken() const
	{
		return _hasBroken;
	}

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

	/** Enumerates over the given enumerable object, if the enumerator has not yet broken. */
	template <typename E>
	void operator()(E&& enumerable)
	{
		if (!_hasBroken)
		{
			for (T i : enumerable)
			{
				auto result = _invoker(_func, std::forward<T>(i));

				if (result == EnumeratorControl::Break)
				{
					_hasBroken = true;
					break;
				}
			}
		}
	}

	////////////////
	///   Data   ///
private:

	bool _hasBroken;
	void* _func;
	EnumeratorControl(*_invoker)(void*, T);
};
