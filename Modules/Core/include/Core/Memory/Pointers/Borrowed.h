// Borrowed.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../ReferenceCounter.h"
#include "Owned.h"

/////////////////
///   Types   ///

/** Represents use of an object, causes runtime failure if the object is destroyed. */
template <typename T>
struct Borrowed final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	template <typename T>
	friend struct Weak;

	////////////////////////
	///   Constructors   ///
private:

	Borrowed(T* value, ReferenceCounter* refCounter)
		: _value(value), _refCounter(refCounter)
	{
		if (refCounter)
		{
			refCounter->AddBorrow();
		}
	}
	Borrowed(const Borrowed& copy)
		: _value(copy._value), _refCounter(copy._refCounter)
	{
		if (_refCounter)
		{
			_refCounter->AddBorrow();
		}
	}
	Borrowed(Borrowed&& move)
		: _value(move._value), _refCounter(move._refCounter)
	{
		move._value = nullptr;
		move._refCounter = nullptr;
	}
	~Borrowed()
	{
		if (_refCounter)
		{
			_refCounter->ReleaseBorrow();
		}
	}

	template <typename F>
	Borrowed(const Borrowed<F>& copy)
		: _value(copy._value), _refCounter(copy._refCounter)
	{
		Borrowed::PointerCompatibilityAssert<F>();

		if (_refCounter)
		{
			_refCounter->AddBorrow();
		}
	}

	template <typename F>
	Borrowed(Borrowed<F>&& move)
		: _value(move._value), _refCounter(move._refCounter)
	{
		Borrowed::PointerCompatibilityAssert<F>();

		if (_refCounter)
		{
			_refCounter->AddBorrow();
		}
	}

	///////////////////
	///   Methods   ///
public:

	T* GetPointer() const
	{
		return _value;
	}

private:

	template <typename F>
	static constexpr void PointerCompatibilityAssert()
	{
		static_assert(std::is_convertible<F*, T*>::value, "The given pointer is not compatible with this Borrow.");
	}

	/////////////////////
	///   Operators   ///
public:

	Borrowed& operator=(const Borrowed& copy) = delete;
	Borrowed& operator=(Borrowed&& move) = delete;

	T& operator*() const
	{
		return *_value;
	}
	T* operator->() const
	{
		return _value;
	}
	operator bool() const
	{
		return _value != nullptr;
	}
	bool operator==(std::nullptr_t) const
	{
		return _value == nullptr;
	}
	bool operator!=(std::nullptr_t) const
	{
		return _value != nullptr;
	}

	////////////////
	///   Data   ///
private:

	T* _value;
	ReferenceCounter* _refCounter;
};

//////////////////////
///   Reflection   ///

template <typename T>
BUILD_TEMPLATE_REFLECTION(Borrowed, T);
