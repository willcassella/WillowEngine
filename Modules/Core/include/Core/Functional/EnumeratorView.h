// EnumeratorView.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <utility>
#include <type_traits>
#include "../Utility/View.h"

enum class EnumeratorResult : byte
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
	{
		static_assert(std::is_same<EnumeratorResult, std::result_of_t<F(T)>>::value || std::is_void<std::result_of_t<F(T)>>::value,
			"Enumerator functions must return either 'void' or 'EnumeratorResult'");

		Setup(func);
		_lastResult = EnumeratorResult::Continue;
	}

    EnumeratorView(EnumeratorView&& move) = delete;
	EnumeratorView(EnumeratorView& copy) = delete;
	EnumeratorView(const EnumeratorView& copy) = delete;

	///////////////////
	///   Methods   ///
public:

	/** Returns whether the enumerator has broken. If it has this EnumeratorView will refuse to continue enumeration,
	* but checking this can save you the trouble of trying. */
	FORCEINLINE bool HasBroken() const
	{
		return _lastResult == EnumeratorResult::Break;
	}

	/** Invokes the enumerator on a single value, if the enumerator has not yet broken. */
	EnumeratorResult Invoke(T value) const
	{
		if (!HasBroken())
		{
			_lastResult = _invoker(_func, std::forward<T>(value));
		}

		return _lastResult;
	}

	/** Invokes the enumerator on an enumerable object, if the enumerator has not yet broken. */
	template <typename E>
	EnumeratorResult Enumerate(E&& enumerable) const
	{
		for (T i : enumerable)
		{
			if (this->Invoke(std::forward<T>(i)) == EnumeratorResult::Break)
			{
				break;
			}
		}

		return _lastResult;
	}

private:

	/** Creates an invoker that decides whether to continue or not. */
	template <typename F>
	auto Setup(F&& func) -> std::enable_if_t<std::is_same<EnumeratorResult, std::result_of_t<F(T)>>::value>
	{
		_func = &func;
		_invoker = [](void* f, T value) -> EnumeratorResult
		{
			return (*static_cast<std::decay_t<F>*>(f))(std::forward<T>(value));
		};
	}

	/** Creates an invoker that always continues. */
	template <typename F>
	auto Setup(F&& func) -> std::enable_if_t<std::is_void<std::result_of_t<F(T)>>::value>
	{
		_func = &func;
		_invoker = [](void* f, T value) -> EnumeratorResult
		{
			(*static_cast<std::decay_t<F>*>(f))(std::forward<T>(value));
			return EnumeratorResult::Continue;
		};
	}

	/////////////////////
	///   Operators   ///
public:

	/** Invokes the enumerator on a single value, if the enumerator has not yet broken. */
	EnumeratorResult operator()(T value) const
	{
		return this->Invoke(std::forward<T>(value));
	}

	////////////////
	///   Data   ///
private:

	void* _func;
	EnumeratorResult(*_invoker)(void*, T);
	mutable EnumeratorResult _lastResult;
};
