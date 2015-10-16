// Nullable.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <cassert>
#include <utility>
#include "../STDExt/TypeTraits.h"
#include "StaticBuffer.h"

template <typename T>
struct Nullable final
{
	////////////////////////
	///   Constructors   ///
public:

	Nullable()
	{
		_hasValue = false;
	}
	Nullable(const Nullable& copy)
		: Nullable()
	{
		self = copy;
	}
	Nullable(Nullable&& move)
		: Nullable()
	{
		self = std::move(move);
	}
	~Nullable()
	{
		Nullify();
	}
	
	template <typename F, WHERE(std::is_constructible<T, F>::value)>
	Nullable(F&& value)
	{
		new (_value.GetValue()) T(std::forward<F>(value));
		_hasValue = true;
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether a value is currently held.
	* NOTE: If this returns 'false', then 'GetValue' will fail. */
	FORCEINLINE bool HasValue() const
	{
		return _hasValue;
	}

	/** Returns the currently held value.
	* WARNING: Check 'HasValue' before calling this. */
	T& GetValue()
	{
		assert(_hasValue);
		return FastGet();
	}

	/** Returns the currently held value.
	* WARNING: Check 'HasValue' before calling this. */
	const T& GetValue() const
	{
		assert(_hasValue);
		return FastGet();
	}

	/** Destroys the currently held value. */
	void Nullify()
	{
		if (_hasValue)
		{
			FastGet().~T();
			_hasValue = false;
		}
	}

private:

	T& FastGet()
	{
		return *_value.template GetValueAs<T>();
	}
	const T& FastGet() const
	{
		return *_value.template GetValueAs<T>();
	}

	/////////////////////
	///   Operators   ///
public:

	Nullable& operator=(const Nullable& copy)
	{
		if (this != &copy)
		{
			if (copy.HasValue())
			{
				self = copy.GetValue();
			}
			else
			{
				Nullify();
			}
		}

		return self;
	}
	Nullable& operator=(Nullable&& move)
	{
		if (this != &move)
		{
			if (move.HasValue())
			{
				// Move and destroy move's value
				self = std::move(move.GetValue());
				move.GetValue().~T();
				move._hasValue = false;
			}
			else
			{
				Nullify();
			}
		}

		return self;
	}

	template <typename F, WHERE(std::is_constructible<T, F>::value)>
	Nullable& operator=(F&& value)
	{
		if (_hasValue)
		{
			GetValue() = std::forward<F>(value);
		}
		else
		{
			new (_value.GetValue()) T(std::forward<F>(value));
			_hasValue = true;
		}

		return self;
	}

	////////////////
	///   Data   ///
private:

	StaticBuffer<sizeof(T)> _value;
	bool _hasValue;
};
