// Pointers.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <utility>
#include "New.h"
#include "../Reflection/Reflection.h"

/////////////////
///   Types   ///

template <typename T>
struct OwnerPtr final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	friend OwnerPtr<void>;
	template <typename F> 
	friend struct OwnerPtr;
	static_assert(!std::is_const<T>::value, "An 'OwnerPtr' may not point to const.");

	////////////////////////
	///   Constructors   ///
public:

	OwnerPtr()
		: _value(nullptr)
	{
		// All done
	}
	OwnerPtr(std::nullptr_t)
		: OwnerPtr()
	{
		// All done
	}
	OwnerPtr(NewPtr<T>&& value)
		: _value(value.TakeValue())
	{
		// All done
	}
	OwnerPtr(const OwnerPtr& copy) = delete;
	OwnerPtr(OwnerPtr&& move)
		: _value(move._value)
	{
		move._value = nullptr;
	}
	~OwnerPtr()
	{
		delete _value;
	}

	template <typename CopyType>
	OwnerPtr(const OwnerPtr<CopyType>& copy) = delete;

	template <typename MoveType, WHERE(std::is_convertible<MoveType*, T*>::value)>
	OwnerPtr(OwnerPtr<MoveType>&& move)
		: _value(move._value)
	{
		move._value = nullptr;
	}

	template <typename ValueType, WHERE(std::is_convertible<ValueType*, T*>::value)>
	OwnerPtr(NewPtr<ValueType>&& value)
		: _value(value.TakeValue())
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	FORCEINLINE T* Get()
	{
		return _value;
	}

	FORCEINLINE const T* Get() const
	{
		return _value;
	}

	FORCEINLINE OwnerPtr<T>&& Transfer()
	{
		return std::move(self);
	}

	/////////////////////
	///   Operators   ///
public:
	
	OwnerPtr& operator=(std::nullptr_t)
	{
		delete _value;
		_value = nullptr;

		return self;
	}
	OwnerPtr& operator=(NewPtr<T>&& value)
	{
		delete _value;
		_value = value.TakeValue();

		return self;
	}
	OwnerPtr& operator=(const OwnerPtr& copy) = delete;
	OwnerPtr& operator=(OwnerPtr&& move)
	{
		if (this != &move)
		{
			delete _value;
			_value = move._value;
		}

		return self;
	}
	T& operator*()
	{
		return *_value;
	}
	const T& operator*() const
	{
		return *_value;
	}
	T* operator->()
	{
		return _value;
	}
	const T* operator->() const
	{
		return _value;
	}
	operator bool() const
	{
		return _value != nullptr;
	}

	template <typename CopyType>
	OwnerPtr& operator=(const OwnerPtr<CopyType>& copy) = delete;

	template <typename MoveType, WHERE(std::is_convertible<MoveType*, T*>::value)>
	OwnerPtr& operator=(OwnerPtr<MoveType>&& move)
	{
		if (this != &move)
		{
			delete _value;
			_value = move._value;
		}

		return self;
	}

	template <typename ValueType, WHERE(std::is_convertible<ValueType*, T*>::value)>
	OwnerPtr& operator=(NewPtr<ValueType>&& value)
	{
		delete _value;
		_value = value.TakeValue();

		return self;
	}

	////////////////
	///   Data   ///
private:

	T* _value;
};

template <>
struct CORE_API OwnerPtr < void > final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	////////////////////////
	///   Constructors   ///
public:

	OwnerPtr();
	OwnerPtr(std::nullptr_t)
		: OwnerPtr()
	{
		// All done
	}
	OwnerPtr(const OwnerPtr& copy) = delete;
	OwnerPtr(OwnerPtr&& move);
	~OwnerPtr();

	template <typename ValueType>
	OwnerPtr(NewPtr<ValueType>&& value)
		: _value(value.TakeValue()), _type(&TypeOf<ValueType>())
	{
		// All done
	}

	template <typename CopyType>
	OwnerPtr(const OwnerPtr<CopyType>& copy) = delete;

	template <typename MoveType>
	OwnerPtr(OwnerPtr<MoveType>&& move)
		: _value(move._value), _type(&TypeOf(*move))
	{
		move._value = nullptr;
	}

	///////////////////
	///   Methods   ///
public:

	// TODO: Documentation
	FORCEINLINE void* Get()
	{
		return _value;
	}

	FORCEINLINE const void* Get() const
	{
		return _value;
	}

	FORCEINLINE const TypeInfo& GetValueType() const
	{
		return *_type;
	}

	FORCEINLINE OwnerPtr&& Transfer()
	{
		return std::move(self);
	}

	/////////////////////
	///   Operators   ///
public:

	OwnerPtr& operator=(std::nullptr_t);
	OwnerPtr& operator=(const OwnerPtr& copy) = delete;
	OwnerPtr& operator=(OwnerPtr&& move);
	Variant operator*();
	ImmutableVariant operator*() const;
	operator bool() const
	{
		return _value != nullptr;
	}

	template <typename ValueType>
	OwnerPtr& operator=(NewPtr<ValueType>&& value)
	{
		self = nullptr;

		_value = value.TakeValue();
		_type = &TypeOf<ValueType>();

		return self;
	}

	template <typename CopyType>
	OwnerPtr& operator=(const OwnerPtr<CopyType>& copy) = delete;

	template <typename MoveType>
	OwnerPtr& operator=(OwnerPtr<MoveType>&& move)
	{
		if (this != &move)
		{
			self = nullptr;

			_value = move._value;
			_type = &TypeOf(*move);

			move._value = nullptr;
		}

		return self;
	}

	////////////////
	///   Data   ///
private:

	void* _value;
	const TypeInfo* _type;
};
