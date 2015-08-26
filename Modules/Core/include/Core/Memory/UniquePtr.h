// UniquePtr.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <utility>
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

	template <typename F, typename ... Args>
	friend UniquePtr<F> New(Args&& ...);

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

	template <typename F>
	UniquePtr(const UniquePtr<F>& copy) = delete;

	template <typename F, WHERE(std::is_convertible<F*, T*>::value)>
	UniquePtr(UniquePtr<F>&& move)
		: _value(move._value)
	{
		move._value = nullptr;
	}

private:

	template <typename NewT>
	UniquePtr(NewT* value)
		: _value(value)
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

	void ToArchive(ArchNode& node) const
	{
		if (_value)
		{
			auto& child = node.AddNode(TypeOf(*_value).GetName());
			::ToArchive(*_value, child);
		}
		else
		{
			node.SetValue("null");
		}
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

	template <typename F>
	UniquePtr& operator=(const UniquePtr<F>& copy) = delete;

	template <typename F, WHERE(std::is_convertible<F*, T*>::value)>
	UniquePtr& operator=(UniquePtr<F>&& move)
	{
		if (this != &move)
		{
			delete _value;
			_value = move._value;
		}

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

	/** UniquePtr cannot be copied. */
	template <typename T>
	UniquePtr(const UniquePtr<T>& copy) = delete;

	/** But it may be moved! */
	template <typename T>
	UniquePtr(UniquePtr<T>&& move)
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

	void ToArchive(ArchNode& node) const
	{
		if (_value)
		{
			auto& child = node.AddNode(_type->GetName());
			::ToArchive(*self, child);
		}
		else
		{
			node.SetValue("null");
		}
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

	template <typename T>
	UniquePtr& operator=(const UniquePtr<T>& copy) = delete;

	template <typename F>
	UniquePtr& operator=(UniquePtr<F>&& move)
	{
		// UniquePtr<void> can never be viewed as another type of UniquePtr, so identity check is not necessary
		self = nullptr;
		_value = move._value;
		_type = &TypeOf(*move);
		move._value = nullptr;

		return self;
	}

	////////////////
	///   Data   ///
private:

	void* _value;
	const TypeInfo* _type;
};

/////////////////////
///   Functions   ///

/** Constructs a new instance of 'T'. */
template <typename T, typename ... Args>
UniquePtr<T> New(Args&& ... args)
{
	return new T(std::forward<Args>(args)...);
}

//////////////////////
///   Reflection   ///

template <typename T>
BUILD_TEMPLATE_REFLECTION(UniquePtr, T);
