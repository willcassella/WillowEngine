// Owned.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../../Application.h"
#include "../../Reflection/StructInfo.h"

/////////////////
///   Types   ///

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

	/** 'Owned' may be constructed with the function 'New'. */
	template <typename F, typename ... ArgT>
	friend Owned<F> New(ArgT&& ... args);

	////////////////////////
	///   Constructors   ///
public:

	Owned()
		: _value(nullptr)
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
		: _value(move._value)
	{
		move._value = nullptr;
	}
	~Owned()
	{
		this->Destroy();
	}

	template <typename F>
	Owned(const Owned<F>& copy) = delete;

	template <typename F>
	Owned(Owned<F>&& move)
		: _value(move._value)
	{
		Owned::PointerCompatibilityAssert<F>();
		move._value = nullptr;
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns a raw pointer to the managed value. */
	FORCEINLINE T* GetPointer()
	{
		return _value;
	}

	/** Returns a raw pointer to the managed value. */
	FORCEINLINE const T* GetPointer() const
	{
		return _value;
	}

private:

	FORCEINLINE void Destroy()
	{
		if (_value)
		{
			_value->~T();
			free(_value);
			_value = nullptr;
		}
	}

	template <typename F>
	static constexpr void PointerCompatibilityAssert()
	{
		static_assert(std::is_convertible<F*, T*>::value, "The given pointer is not compatible.");
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
			move._value = nullptr;
		}

		return *this;
	}

	template <typename F>
	Owned& operator=(const Owned<F>& copy) = delete;

	template <typename F>
	Owned& operator=(Owned<F>&& move)
	{
		Owned::PointerCompatibilityAssert<F>();

		this->Destroy();
		_value = move._value;
		move._value = nullptr;

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
};

template <>
struct CORE_API Owned < void > final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	////////////////////////
	///   Constructors   ///
public:

	Owned()
		: _value(nullptr), _type(nullptr)
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
		: _value(move._value), _type(move._type)
	{
		move._value = nullptr;
		move._type = nullptr;
	}
	~Owned()
	{
		this->Destroy();
	}

	template <typename T>
	Owned(const Owned<T>& copy) = delete;

	template <typename T>
	Owned(Owned<T>&& move)
		: _value(move._value), _type(move ? &TypeOf(*move) : nullptr)
	{
		move._value = nullptr;
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns a raw pointer to the managed value. */
	FORCEINLINE void* GetPointer()
	{
		return _value;
	}

	/** Returns a raw pointer to the managed value. */
	FORCEINLINE const void* GetPointer() const
	{
		return _value;
	}

	const TypeInfo* GetManagedType() const
	{
		return _type;
	}

private:

	FORCEINLINE void Destroy()
	{
		if (_value)
		{
			_type->GetDestructor()(_value);
			free(_value);
			_value = nullptr;
			_type = nullptr;
		}
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
			move._value = nullptr;
			move._type = nullptr;
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
		move._value = nullptr;

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
};

//////////////////////
///   Reflection   ///

template <typename T>
BUILD_TEMPLATE_REFLECTION(Owned, T);

//////////////////////
///   Operations   ///

namespace Operations
{
	/** Implementation of 'ToArchive' for Owned. */
	template <typename T>
	struct ToArchive< Owned<T> > final
	{
		static void Function(const Owned<T>& value, ArchiveWriter& writer)
		{
			if (value != nullptr)
			{
				writer.PushValue(TypeOf(*value).GetName(), *value);
			}
			else
			{
				writer.SetValue(nullptr);
			}
		}

		static constexpr bool Supported = ToArchive<T>::Supported;
	};

	/** Implementation of 'ToArchive' for Owned<void>. */
	template <>
	struct CORE_API ToArchive < Owned<void> > final
	{
		static void Function(const Owned<void>& value, ArchiveWriter& writer);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromArchive' for Owned<T>. */
	template <typename T>
	struct FromArchive< Owned<T> > final
	{
		static void Function(Owned<T>& value, const ArchiveReader& reader)
		{
			if (reader.IsNull())
			{
				value = nullptr;
			}
			else
			{
				// TODO
				//reader.GetFirstChild([&](const ArchiveReader& child)
				//{
				//	auto type = Application::FindType(child.GetName());
				//});
			}
		}

		static constexpr bool Supported = FromArchive<T>::Supported;
	};

	/** Implementation of 'FromArchive' for Owned<void>. */
	template <>
	struct CORE_API FromArchive < Owned<void> > final
	{
		static void Function(Owned<void>& value, const ArchiveReader& reader);

		static constexpr bool Supported = true;
	};
}
