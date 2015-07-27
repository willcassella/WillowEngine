// New.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <cassert>
#include <type_traits>
#include "../config.h"

/////////////////
///   Types   ///

/** A temporary type that acts as an intermediary between creating values
* with "New", and storing them in a smart pointer. */
template <typename T>
struct NewPtr final
{
	///////////////////////
	///   Information   ///
public:

	template <typename F, typename ... Args> friend NewPtr<F> New(Args&&... args);

	////////////////////////
	///   Constructors   ///
public:

	NewPtr(const NewPtr& copy) = delete;
	NewPtr(NewPtr&& move) = delete;
	~NewPtr()
	{
		assert(_value == nullptr); // You must capture the result of "New" in a smart pointer.
		delete _value;
	}

private:

	NewPtr(T* value)
		: _value(value)
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Steals the value from this NewPtr, nullifying it in the process. */
	FORCEINLINE T* TakeValue()
	{
		T* value = _value;
		_value = nullptr;

		return value;
	}

	/////////////////////
	///   Operators   ///
public:

	NewPtr& operator=(const NewPtr& copy) = delete;
	NewPtr& operator=(NewPtr&& move) = delete;

	////////////////
	///   Data   ///
private:

	T* _value;
};

/////////////////////
///   Functions   ///

/** Constructs a new instance */
template <typename T, typename ... Args>
NewPtr<T> New(Args&&... args)
{
	return new T(std::forward<Args>(args)...);
}
