// Nullable.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <cassert>
#include "../STDE/TypeTraits.h"
#include "StaticBuffer.h"

template <typename T>
struct Nullable final
{
	///////////////////////
	///   Information   ///
public:

	template <typename F>
	friend struct Nullable;

	////////////////////////
	///   Constructors   ///
public:

	Nullable()
		: _hasValue(false)
	{
		// All done
	}
	Nullable(const Nullable& copy)
	{
		if (copy.HasValue())
		{
			this->PlaceValue(copy.FastGet());
		}
		else
		{
			_hasValue = false;
		}
	}
	Nullable(Nullable&& move)
	{
		if (move.HasValue())
		{
			this->PlaceValue(std::move(move.FastGet()));
		}
		else
		{
			_hasValue = false;
		}
	}
	~Nullable()
	{
		if (_hasValue)
		{
			this->FastGet().~T();
		}
	}

	template <typename F>
	Nullable(const Nullable<F>& copy)
	{
		if (copy.HasValue())
		{
			this->PlaceValue(copy.FastGet());
		}
		else
		{
			_hasValue = false;
		}
	}

	template <typename F>
	Nullable(Nullable<F>&& move)
	{
		if (move.HasValue())
		{
			this->PlaceValue(std::move(move.FastGet()));
		}
		else
		{
			_hasValue = false;
		}
	}

	template <typename F, WHERE(!std::is_same<F, Nullable>::value)>
	Nullable(F&& value)
	{
		this->PlaceValue(std::forward<F>(value));
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
	T& GetValue() &
	{
		assert(_hasValue);
		return FastGet();
	}

	/** Returns the currently held value.
	* WARNING: Check 'HasValue' before calling this. */
	const T& GetValue() const &
	{
		assert(_hasValue);
		return FastGet();
	}

	/** Since this is a temporary object, you couldn't have possibly checked if it contains a value. */
	T&& GetValue() && = delete;

	/** Sets the given receptor to the currently held value, if it exists.
	* Returns whether the receptor was set or not. */
	bool GetValue(T& receptor) const &
	{
		if (_hasValue)
		{
			receptor = FastGet();
			return true;
		}
		else
		{
			return false;
		}
	}

	/** Sets the given receptor to the currently held value, if it exists.
	* Returns whether the receptor was set or not. */
	bool GetValue(T& receptor) &&
	{
		if (_hasValue)
		{
			receptor = std::move(FastGet());
			return true;
		}
		else
		{
			return false;
		}
	}

	/** Invokes the given function object on the contained value, if it exists. Otherwise does nothing.
	* Returns whether the given function was executed. */
	template <typename Func>
	bool Invoke(const Func& func) &
	{
		if (this->HasValue())
		{
			func(this->FastGet());
			return true;
		}
		else
		{
			return false;
		}
	}

	/** Invokes the given function object on the contained value, if it exists. Otherwise does nothing.
	* Returns whether the given function was executed. */
	template <typename Func>
	bool Invoke(const Func& func) const &
	{
		if (this->HasValue())
		{
			func(this->FastGet());
			return true;
		}
		else
		{
			return false;
		}
	}

	/** Invokes the given function object on the contained value, if it exists. Otherwise does nothing.
	* Returns whether the given function was executed. */
	template <typename Func>
	bool Invoke(const Func& func) &&
	{
		if (this->HasValue())
		{
			func(std::move(this->FastGet()));
			return true;
		}
		else
		{
			return false;
		}
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

	/** Returns a reference to the value, without checking whether one exists. */
	T& FastGet()
	{
		return *_buffer.template GetPointer<T>();
	}

	/** Returns a reference to the value, without checking whether one exists. */
	const T& FastGet() const
	{
		return *_buffer.template GetPointer<T>();
	}
	
	/** Constructs an instance of 'T' with the given value, without checking whether a current value exists. */
	template <typename F>
	void PlaceValue(F&& value)
	{
		_buffer.template Emplace<T>(std::forward<F>(value));
		_hasValue = true;
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
				*this = copy.FastGet();
			}
			else
			{
				Nullify();
			}
		}

		return *this;
	}
	Nullable& operator=(Nullable&& move)
	{
		if (this != &move)
		{
			if (move.HasValue())
			{
				*this = std::move(move.FastGet());
			}
			else
			{
				Nullify();
			}
		}

		return *this;
	}

	template <typename F>
	Nullable& operator=(const Nullable<F>& copy)
	{
		if (copy.HasValue())
		{
			*this = copy.FastGet();
		}
		else
		{
			Nullify();
		}

		return *this;
	}

	template <typename F>
	Nullable& operator=(Nullable<F>&& move)
	{
		if (move.HasValue())
		{
			*this = std::move(move.FastGet());
		}
		else
		{
			Nullify();
		}

		return *this;
	}

	template <typename F, WHERE(!std::is_same<F, Nullable>::value)>
	Nullable& operator=(F&& value)
	{
		if (_hasValue)
		{
			FastGet() = std::forward<F>(value);
		}
		else
		{
			PlaceValue(std::forward<F>(value));
		}

		return *this;
	}

	////////////////
	///   Data   ///
private:

	StaticBuffer<sizeof(T)> _buffer;
	bool _hasValue;
};
