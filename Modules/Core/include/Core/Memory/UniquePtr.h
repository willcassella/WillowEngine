// UniquePtr.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <utility>
#include "New.h"
#include "../Reflection/StructInfo.h"

/////////////////
///   Types   ///

/** "UniquePtr" is a pointer that may be moved but not copied, as the lifetime of what it
* points to is bound to the lifetime of the pointer itself. */
template <typename T>
struct UniquePtr final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	friend UniquePtr<void>;
	template <typename F> 
	friend struct UniquePtr;
	static_assert(!std::is_const<T>::value, "An 'UniquePtr' may not point to const.");

	////////////////////////
	///   Constructors   ///
public:

	UniquePtr()
		: _value(nullptr)
	{
		// All done
	}
	UniquePtr(std::nullptr_t)
		: UniquePtr()
	{
		// All done
	}
	UniquePtr(NewPtr<T>&& value)
		: _value(value.TakeValue())
	{
		// All done
	}
	UniquePtr(const UniquePtr& copy) = delete;
	UniquePtr(UniquePtr&& move)
		: _value(move._value)
	{
		move._value = nullptr;
	}
	~UniquePtr()
	{
		delete _value;
	}

	template <typename CopyType>
	UniquePtr(const UniquePtr<CopyType>& copy) = delete;

	template <typename MoveType, WHERE(std::is_convertible<MoveType*, T*>::value)>
	UniquePtr(UniquePtr<MoveType>&& move)
		: _value(move._value)
	{
		move._value = nullptr;
	}

	template <typename ValueType, WHERE(std::is_convertible<ValueType*, T*>::value)>
	UniquePtr(NewPtr<ValueType>&& value)
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

	FORCEINLINE UniquePtr<T>&& Transfer()
	{
		return std::move(self);
	}

	/////////////////////
	///   Operators   ///
public:
	
	UniquePtr& operator=(std::nullptr_t)
	{
		delete _value;
		_value = nullptr;

		return self;
	}
	UniquePtr& operator=(NewPtr<T>&& value)
	{
		delete _value;
		_value = value.TakeValue();

		return self;
	}
	UniquePtr& operator=(const UniquePtr& copy) = delete;
	UniquePtr& operator=(UniquePtr&& move)
	{
		if (this != &move)
		{
			delete _value;
			_value = move._value;
			move._value = nullptr;
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
	UniquePtr& operator=(const UniquePtr<CopyType>& copy) = delete;

	template <typename MoveType, WHERE(std::is_convertible<MoveType*, T*>::value)>
	UniquePtr& operator=(UniquePtr<MoveType>&& move)
	{
		if (this != &move)
		{
			delete _value;
			_value = move._value;
		}

		return self;
	}

	template <typename ValueType, WHERE(std::is_convertible<ValueType*, T*>::value)>
	UniquePtr& operator=(NewPtr<ValueType>&& value)
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
struct CORE_API UniquePtr < void > final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	////////////////////////
	///   Constructors   ///
public:

	UniquePtr();
	UniquePtr(std::nullptr_t)
		: UniquePtr()
	{
		// All done
	}
	UniquePtr(const UniquePtr& copy) = delete;
	UniquePtr(UniquePtr&& move);
	~UniquePtr();

	template <typename ValueType>
	UniquePtr(NewPtr<ValueType>&& value)
		: _value(value.TakeValue()), _type(&TypeOf<ValueType>())
	{
		// All done
	}

	template <typename CopyType>
	UniquePtr(const UniquePtr<CopyType>& copy) = delete;

	template <typename MoveType>
	UniquePtr(UniquePtr<MoveType>&& move)
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

	FORCEINLINE UniquePtr&& Transfer()
	{
		return std::move(self);
	}

	/////////////////////
	///   Operators   ///
public:

	UniquePtr& operator=(std::nullptr_t);
	UniquePtr& operator=(const UniquePtr& copy) = delete;
	UniquePtr& operator=(UniquePtr&& move);
	Variant operator*();
	ImmutableVariant operator*() const;
	operator bool() const
	{
		return _value != nullptr;
	}

	template <typename ValueType>
	UniquePtr& operator=(NewPtr<ValueType>&& value)
	{
		self = nullptr;

		_value = value.TakeValue();
		_type = &TypeOf<ValueType>();

		return self;
	}

	template <typename CopyType>
	UniquePtr& operator=(const UniquePtr<CopyType>& copy) = delete;

	template <typename MoveType>
	UniquePtr& operator=(UniquePtr<MoveType>&& move)
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

//////////////////////
///   Reflection   ///

template <typename T>
BUILD_TEMPLATE_REFLECTION(UniquePtr, T);
