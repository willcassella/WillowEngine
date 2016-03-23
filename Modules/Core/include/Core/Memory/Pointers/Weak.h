// Weak.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Borrowed.h"

/////////////////
///   Types   ///

template <class T>
struct Weak final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	////////////////////////
	///   Constructors   ///
public:

	Weak()
		: _value(nullptr), _refCounter(nullptr)
	{
		// All done
	}
	Weak(std::nullptr_t)
		: Weak()
	{
		// All done
	}
	Weak(T* value)
	{
		if (value)
		{
			_value = value;
			_refCounter = _value->GetReferenceCounter();
			_refCounter->AddWeakRef();
		}
		else
		{
			_value = nullptr;
			_refCounter = nullptr;
		}
	}
	Weak(T& value)
	{
		_value = &value;
		_refCounter = value.GetReferenceCounter();
		_refCounter->AddWeakRef();
	}
	Weak(const Weak& copy)
	{
		if (copy)
		{
			_value = copy._value;
			_refCounter = copy._refCounter;
			_refCounter->AddWeakRef();
		}
		else
		{
			_value = nullptr;
			_refCounter = nullptr;
		}
	}
	Weak(Weak&& move)
		: _value(move._value), _refCounter(move._refCounter)
	{
		move._value = nullptr;
		move._refCounter = nullptr;
	}
	~Weak()
	{
		this->ReleaseReference();
	}

	template <class F>
	Weak(const Weak<F>& copy)
	{
		Weak::PointerCompatibilityAssert<F>();
		
		if (copy)
		{
			_value = copy._value;
			_refCounter = copy._refCounter;
			_refCounter->AddWeakRef();
		}
		else
		{
			_value = nullptr;
			_refCounter = nullptr;
		}
	}

	template <typename F>
	Weak(Owned<F>& owner)
		: Weak(owner.GetPointer())
	{
		Weak::PointerCompatibilityAssert<F>();
	}

	template <typename F>
	Weak(const Owned<F>& owner)
		: Weak(owner.GetPointer())
	{
		Weak::PointerCompatibilityAssert<F>();
	}

	template <typename F>
	Weak(Owned<F>&& owner) = delete;

	template <class F>
	Weak(const Borrowed<T>& borrow)
		: Weak(borrow.GetPointer())
	{
		Weak::PointerCompatibilityAssert<F>();
	}

	///////////////////
	///   Methods   ///
public:

	FORCEINLINE T* GetPointer() const
	{
		if (_value && !_refCounter->IsDestroyed())
		{
			return _value;
		}
		else
		{
			return nullptr;
		}
	}

	Borrowed<T> Borrow() const
	{
		return{ _value, _refCounter };
	}

private:

	FORCEINLINE void ReleaseReference() const
	{
		if (_refCounter)
		{
			_refCounter->ReleaseWeakRef();
		}
	}

	template <typename F>
	static constexpr void PointerCompatibilityAssert()
	{
		static_assert(std::is_convertible<F*, T*>::value, "The given pointer is not compatible with this Weak pointer.");
	}

	/////////////////////
	///   Operators   ///
public:

	Weak& operator=(std::nullptr_t)
	{
		this->ReleaseReference();
		_value = nullptr;
		_refCounter = nullptr;

		return *this;
	}
	Weak& operator=(T* value)
	{
		if (value)
		{
			*this = *value;
		}
		else
		{
			*this = nullptr;
		}

		return *this;
	}
	Weak& operator=(T& value)
	{
		if (_value != &value)
		{
			this->ReleaseReference();
			_value = &value;
			_refCounter = value.GetReferenceCounter();
			_refCounter->AddWeakRef();
		}

		return *this;
	}
	Weak& operator=(const Weak& copy)
	{
		if (this != &copy)
		{
			this->ReleaseReference();

			if (copy)
			{
				_value = copy._value;
				_refCounter = copy._refCounter;
				_refCounter->AddWeakRef();
			}
			else
			{
				_value = nullptr;
				_refCounter = nullptr;
			}
		}

		return *this;
	}
	Weak& operator=(Weak&& move)
	{
		if (this != &move)
		{
			this->ReleaseReference();

			_value = move._value;
			_refCounter = move._refCounter;
			move._value = nullptr;
			move._refCounter = nullptr;
		}

		return *this;
	}
	
	template <class F>
	Weak& operator=(const Weak<F>& copy)
	{
		Weak::PointerCompatibilityAssert<F>();

		if (_value != copy._value)
		{
			this->ReleaseReference();

			if (copy)
			{
				_value = copy._value;
				_refCounter = copy._refCounter;
				_refCounter->AddWeakRef();
			}
			else
			{
				_value = nullptr;
				_refCounter = nullptr;
			}
		}

		return *this;
	}

	template <class F>
	Weak& operator=(Weak<F>&& move)
	{
		Weak::PointerCompatibilityAssert<F>();

		if (_value != move._value)
		{
			this->ReleaseReference();

			_value = move._value;
			_refCounter = move._refCounter;
			_value = nullptr;
			_refCounter = nullptr;
		}

		return *this;
	}

	template <typename F>
	Weak& operator=(Owned<F>& owner)
	{
		Weak::PointerCompatibilityAssert<F>();
		*this = owner.GetPointer();
		return *this;
	}

	template <typename F>
	Weak& operator=(const Owned<F>& owner)
	{
		Weak::PointerCompatibilityAssert<F>();
		*this = owner.GetPointer();
		return *this;
	}

	template <typename F>
	Weak& operator=(Owned<F>&& owner) = delete;

	template <class F>
	Weak& operator=(const Borrowed<F>& borrow)
	{
		Weak::PointerCompatibilityAssert<F>();
		*this = borrow.GetPointer();
		return *this;
	}

	operator bool() const
	{
		return this->GetPointer() != nullptr;
	}
	bool operator==(std::nullptr_t) const
	{
		return this->GetPointer() == nullptr;
	}
	bool operator!=(std::nullptr_t) const
	{
		return this->GetPointer() != nullptr;
	}

	////////////////
	///   Data   ///
private:

	T* _value;
	ReferenceCounter* _refCounter;
};

//////////////////////
///   Operations   ///

namespace Operations
{
	/** Implementation of 'ToArchive' for Weak */
	template <typename T>
	struct ToArchive < Weak<T> > final
	{
		static void Function(const Weak<T>& value, ArchiveWriter& writer)
		{
			writer.SetValue(value.GetPointer());
		}

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromArchive' for Weak */
	template <typename T>
	struct FromArchive < Weak<T> > final
	{
		static void Function(Weak<T>& value, const ArchiveReader& reader)
		{
			T* pointer;
			reader.GetValue(pointer);

			value = pointer;
		}

		static constexpr bool Supported = true;
	};
}

//////////////////////
///   Reflection   ///

template <typename T>
BUILD_TEMPLATE_REFLECTION(Weak, T);
