// Owned.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../../Application.h"
#include "../../Reflection/StructInfo.h"

/////////////////
///   Types   ///

/** Function signature used for deleters. */
using DeleterFunc = void(void*, const TypeInfo*);

/** This is a pointer that may be moved but not copied, as the lifetime of what it
* points to is bound to the lifetime of the pointer itself. */
template <typename T>
struct Owned final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	/** Different instances of 'Owned' need to access eachother's members. */
	template <typename F>
	friend struct Owned;

	////////////////////////
	///   Constructors   ///
public:

	Owned()
		: _value(nullptr), _deleter(nullptr)
	{
		// All done
	}
	Owned(std::nullptr_t)
		: Owned()
	{
		// All done
	}
	Owned(const Owned& copy) = delete;
	Owned(Owned&& move)
		: _value(move._value), _deleter(move._deleter)
	{
		move._value = nullptr;
		move._deleter = nullptr;
	}
	~Owned()
	{
		this->Destroy();
	}

	template <typename F>
	Owned(const Owned<F>& copy) = delete;

	template <typename F>
	Owned(Owned<F>&& move)
		: _value(move._value), _deleter(move._deleter)
	{
		move._value = nullptr;
		move._deleter = nullptr;
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns a raw pointer to the managed value. */
	FORCEINLINE T* GetManagedPointer()
	{
		return _value;
	}

	/** Returns a raw pointer to the managed value. */
	FORCEINLINE const T* GetManagedPointer() const
	{
		return _value;
	}

	/** Returns a pointer to the type of the managed value. 
	* NOTE: Returns 'null' is this Owned is null. */
	FORCEINLINE const auto* GetManagedType() const
	{
		if (_value)
		{
			return &TypeOf(*_value);
		}
		else
		{
			return nullptr;
		}
	}

	/** Returns a 'Pair' consisting of the value and the deleter, releasing ownership from this Owned. */
	Pair<T*, DeleterFunc*> ReleaseOwnership()
	{
		auto result = MakePair(_value, _deleter);
		_value = nullptr;
		_deleter = nullptr;

		return result;
	}

	/** Explicitly creates a new Owned<T> object, with the given value and deleter.
	* NOTE: The deleter is responsible for calling the value's destructor, as well as deallocating memory.
	* NOTE: The TypeInfo pointer passed into the deleter is the result of the expression "&TypeOf(*value)", or 'null' if the value is null.
	* NOTE: Either the value or the deleter may be null.
	* If both the value and the deleter are null, you've created a null Owned. I hope you're happy.
	* If the value is null but the deleter is not, the deleter will be invoked on a null pointer when the created Owned is destroyed.
	* If the deleter is null but the value is not, nothing will happen when the created Owned is destroyed.
	* The responsibility for handling these cases is left to the caller of this function. */
	static Owned Create(T* value, DeleterFunc* deleter)
	{
		Owned owner;
		owner._value = value;
		owner._deleter = deleter;
		return owner;
	}

private:

	FORCEINLINE void Destroy()
	{
		if (_deleter)
		{
			_deleter(_value, _value ? &TypeOf(*_value) : nullptr);
		}

		_value = nullptr;
		_deleter = nullptr;
	}

	/////////////////////
	///   Operators   ///
public:

	Owned& operator=(std::nullptr_t)
	{
		this->Destroy();
		return *this;
	}
	Owned& operator=(const Owned& copy) = delete;
	Owned& operator=(Owned&& move)
	{
		if (this != &move)
		{
			this->Destroy();
			_value = move._value;
			_deleter = move._deleter;
			move._value = nullptr;
			move._deleter = nullptr;
		}

		return *this;
	}

	template <typename F>
	Owned& operator=(const Owned<F>& copy) = delete;

	template <typename F>
	Owned& operator=(Owned<F>&& move)
	{
		this->Destroy();
		_value = move._value;
		_deleter = move._deleter;
		move._value = nullptr;
		move._deleter = nullptr;

		return *this;
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
	bool operator==(std::nullptr_t) const
	{
		return _value == nullptr;
	}
	bool operator!=(std::nullptr_t) const
	{
		return _value != nullptr;
	}

	operator T*() &
	{
		return _value;
	}
	operator const T*() const &
	{
		return _value;
	}

	////////////////
	///   Data   ///
private:

	T* _value;
	DeleterFunc* _deleter;
};

template <>
struct CORE_API Owned < void > final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	/** Different instances of 'Owned' need to access eachother's members. */
	template <typename F>
	friend struct Owned;

	////////////////////////
	///   Constructors   ///
public:

	Owned()
		: _value(nullptr), _type(nullptr), _deleter(nullptr)
	{
		// All done
	}
	Owned(std::nullptr_t)
		: Owned()
	{
		// All done
	}
	Owned(const Owned& copy) = delete;
	Owned(Owned&& move)
		: _value(move._value), _type(move._type), _deleter(move._deleter)
	{
		move._value = nullptr;
		move._type = nullptr;
		move._deleter = nullptr;
	}
	~Owned()
	{
		this->Destroy();
	}

	template <typename T>
	Owned(const Owned<T>& copy) = delete;

	template <typename T>
	Owned(Owned<T>&& move)
		: _value(move._value), _type(move ? &TypeOf(*move) : nullptr), _deleter(move._deleter)
	{
		move._value = nullptr;
		move._deleter = nullptr;
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns a raw pointer to the managed value. */
	FORCEINLINE void* GetManagedPointer()
	{
		return _value;
	}

	/** Returns a raw pointer to the managed value. */
	FORCEINLINE const void* GetManagedPointer() const
	{
		return _value;
	}

	/** Returns a pointer to the managed value's type.
	* NOTE: This returns null if this Owned is null. */
	FORCEINLINE const TypeInfo* GetManagedType() const
	{
		return _type;
	}

	/** Returns a 'Pair' consisting of the value and the deleter, releasing ownership from this Owned. */
	Pair<void*, DeleterFunc*> ReleaseOwnership()
	{
		auto temp = MakePair(_value, _deleter);
		_value = nullptr;
		_type = nullptr;
		_deleter = nullptr;

		return temp;
	}

	/** Explicitly creates a new Owned<T> object, with the given value and deleter.
	* NOTE: The deleter is responsible for calling the value's destructor, as well as deallocating memory.
	* NOTE: The TypeInfo pointer passed into the deleter is the same as the one passed into this function.
	* NOTE: Any of the given values may be null.
	* If both the value and the deleter are null, you've created a null Owned. I hope you're happy.
	* If the value is null but the deleter is not, the deleter will be invoked on a null pointer when the created Owned is destroyed.
	* If the deleter is null but the value is not, nothing will happen when the created Owned is destroyed.
	* The responsibility for handling these cases is left to the caller of this function. */
	static Owned Create(void* value, const TypeInfo* type, DeleterFunc* deleter)
	{
		Owned owner;
		owner._value = value;
		owner._type = type;
		owner._deleter = deleter;

		return owner;
	}

private:

	FORCEINLINE void Destroy()
	{
		if (_deleter)
		{
			_deleter(_value, _type);
		}

		_value = nullptr;
		_type = nullptr;
		_deleter = nullptr;
	}

	/////////////////////
	///   Operators   ///
public:

	Owned& operator=(std::nullptr_t)
	{
		this->Destroy();
		return *this;
	}
	Owned& operator=(const Owned& copy) = delete;
	Owned& operator=(Owned&& move)
	{
		if (this != &move)
		{
			this->Destroy();
			_value = move._value;
			_type = move._type;
			_deleter = move._deleter;
			move._value = nullptr;
			move._type = nullptr;
			move._deleter = nullptr;
		}

		return *this;
	}
	
	template <typename T>
	Owned& operator=(const Owned<T>& copy) = delete;

	template <typename T>
	Owned& operator=(Owned<T>&& move)
	{
		this->Destroy();
		_value = move._value;
		_type = move ? &TypeOf(*move) : nullptr;
		_deleter = move._deleter;
		move._value = nullptr;
		move._deleter = nullptr;

		return *this;
	}
	
	Variant operator*();
	ImmutableVariant operator*() const;
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

	void* _value;
	const TypeInfo* _type;
	DeleterFunc* _deleter;
};

template <typename TargetT, typename T>
Owned<TargetT> PointerCast(Owned<T>&& owner)
{
	if (owner != nullptr && IsCastableTo<TargetT>(*owner))
	{
		auto pair = owner.ReleaseOwnership();
		return Owned<TargetT>::Create(reinterpret_cast<TargetT*>(pair.First), pair.Second);
	}
	else
	{
		return nullptr;
	}
}

template <typename TargetT, typename T>
Owned<TargetT> StaticPointerCast(Owned<T>&& owner)
{
	auto pair = owner.ReleaseOwnership();
	return Owned<TargetT>::Create(static_cast<TargetT*>(pair.First), pair.Second);
}

//////////////////////
///   Reflection   ///

template <typename T>
BUILD_TEMPLATE_REFLECTION(Owned, T);
