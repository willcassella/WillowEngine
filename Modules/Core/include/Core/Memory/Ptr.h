// Ptr.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Object.h"
#include "OwnerPtr.h"

template <class T>
struct Ptr final
{
	////////////////////////
	///   Constructors   ///
public:

	Ptr()
		: _value(nullptr)
	{
		static_assert(std::is_base_of<Object, T>::value || std::is_base_of<Interface, T>::value,
			"The template parameter for 'Ptr' must extend either 'Object' or 'Interface'.");
	}
	Ptr(std::nullptr_t)
		: Ptr()
	{
		// All done
	}
	Ptr(T* value)
		: _value(value)
	{
		RegisterReference();
	}
	Ptr(const Ptr& copy)
		: _value(copy._value)
	{
		RegisterReference();
	}
	~Ptr()
	{
		UnregisterReference();
	}

	template <class CopyType>
	Ptr(const Ptr<CopyType>& copy)
		: _value(copy._value)
	{
		RegisterReference();
	}

	template <class OwnerType>
	Ptr(OwnerPtr<OwnerType>& owner)
		: _value(owner.Get())
	{
		RegisterReference();
	}

	template <class OwnerType>
	Ptr(const OwnerPtr<OwnerType>& owner)
		: _value(owner.Get())
	{
		RegisterReference();
	}

	template <class OwnerType>
	Ptr(OwnerPtr<OwnerType>&& owner) = delete;

	///////////////////
	///   Methods   ///
public:

	FORCEINLINE T* Get() const
	{
		return _value;
	}

private:

	FORCEINLINE void RegisterReference()
	{
		static_assert(std::is_base_of<Object, T>::value || std::is_base_of<Interface, T>::value, 
			"The template parameter for 'Ptr' must extend either 'Object' or 'Interface'.");

		if (_value)
		{
			_value->_references.Add(reinterpret_cast<void*>(&_value));
		}
	}
	FORCEINLINE void UnregisterReference()
	{
		if (_value)
		{
			_value->_references.DeleteFirst(reinterpret_cast<void*>(&_value));
			_value = nullptr;
		}
	}

	/////////////////////
	///   Operators   ///
public:

	Ptr& operator=(std::nullptr_t)
	{
		UnregisterReference();
		_value = nullptr;
		return self;
	}
	Ptr& operator=(T* value)
	{
		if (_value != value)
		{
			UnregisterReference();
			_value = value;
			RegisterReference();
		}

		return self;
	}
	Ptr& operator=(const Ptr& copy)
	{
		if (_value != copy._value)
		{
			UnregisterReference();
			_value = copy._value;
			RegisterReference();
		}

		return self;
	}
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

	template <class CopyType>//, WHERE(std::is_base_of<ObjectType, CopyType>::value)>
	Ptr& operator=(const Ptr<CopyType>& copy)
	{
		if (_value != copy._value)
		{
			UnregisterReference();
			_value = copy._value;
			RegisterReference();
		}

		return self;
	}

	template <class OwnerType>//, WHERE(std::is_base_of<ObjectType, OwnerType>::value)>
	Ptr& operator=(OwnerPtr<OwnerType>& owner)
	{
		if (_value != owner.Get())
		{
			UnregisterReference();
			_value = owner.Get();
			RegisterReference();
		}

		return self;
	}

	template <class OwnerType>//, WHERE(std::is_base_of<ObjectType, OwnerType>::value && std::is_const<ObjectType>::value)>
	Ptr& operator=(const OwnerPtr<OwnerType>& owner)
	{
		if (_value != owner.Get())
		{
			UnregisterReference();
			_value = owner.Get();
			RegisterReference();
		}

		return self;
	}

	template <class OwnerType>
	Ptr& operator=(OwnerPtr<OwnerType>&& owner) = delete;

	////////////////
	///   Data   ///
private:

	T* _value;
};
