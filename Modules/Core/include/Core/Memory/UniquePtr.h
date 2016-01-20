// UniquePtr.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Reflection/StructInfo.h"
#include "New.h"

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

	/** Different instances of the UniquePtr type need to access eachother's members. */
	template <typename F> 
	friend struct UniquePtr;

	////////////////////////
	///   Constructors   ///
public:

	UniquePtr()
		: _controller(nullptr)
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
		: _controller(move._controller)
	{
		move._controller = nullptr;
	}
	~UniquePtr()
	{
		this->Destroy();
	}

	template <typename F>
	UniquePtr(const UniquePtr<F>& copy) = delete;

	template <typename F, WHERE(std::is_convertible<F*, T*>::value)>
	UniquePtr(UniquePtr<F>&& move)
		: _controller(move._controller)
	{
		move._controller = nullptr;
	}

	template <typename F, WHERE(std::is_convertible<F*, T*>::value)>
	UniquePtr(NewPtr<F>&& value)
	{
		_controller = value.TakeOwnership();
		_controller->GetRefCounter().SetOwnership(OwnershipType::Unique);
	}

	///////////////////
	///   Methods   ///
public:

	FORCEINLINE T* Get()
	{
		return (T*)_controller->GetData();
	}

	FORCEINLINE const T* Get() const
	{
		return (T*)_controller->GetData();
	}

	FORCEINLINE UniquePtr<T>&& Transfer()
	{
		return std::move(self);
	}

	void ToArchive(ArchiveNode& node) const
	{
		if (_controller)
		{
			if (std::is_polymorphic<T>::value)
			{
				// Since T is polymorphic, we need to document value's type
				auto child = node.AddChild(_controller->GetAllocatedType().GetName());
				::ToArchive(*self, *child);
			}
			else
			{
				::ToArchive(*self, node);
			}
		}
		else
		{
			node.SetValue("null");
		}
	}

	void FromArchive(const ArchiveNode& node)
	{
		if (node.GetValue() != "null")
		{
			// TODO: Implement this
		}
		else
		{
			self = nullptr;
		}
	}

private:

	FORCEINLINE void Destroy()
	{
		if (_controller)
		{
			_controller->GetRefCounter().ReleaseOwnerRef();
			_controller->Destroy();
			_controller = nullptr;
		}
	}

	/////////////////////
	///   Operators   ///
public:

	UniquePtr& operator=(std::nullptr_t)
	{
		this->Destroy();
		return self;
	}
	UniquePtr& operator=(const UniquePtr& copy) = delete;
	UniquePtr& operator=(UniquePtr&& move)
	{
		if (this != &move)
		{
			this->Destroy();
			_controller = move._controller;
			move._controller = nullptr;
		}

		return self;
	}
	T& operator*()
	{
		return *Get();
	}
	const T& operator*() const
	{
		return *Get();
	}
	T* operator->()
	{
		return Get();
	}
	const T* operator->() const
	{
		return Get();
	}
	operator bool() const
	{
		return _controller != nullptr;
	}
	bool operator==(std::nullptr_t) const
	{
		return _controller == nullptr;
	}
	bool operator!=(std::nullptr_t) const
	{
		return _controller != nullptr;
	}

	operator T*() &
	{
		return this->Get();
	}
	operator const T*() const &
	{
		return this->Get();
	}

	template <typename F>
	UniquePtr& operator=(const UniquePtr<F>& copy) = delete;

	template <typename F, WHERE(std::is_convertible<F*, T*>::value)>
	UniquePtr& operator=(UniquePtr<F>&& move)
	{
		this->Destroy();
		_controller = move._controller;
		move._controller = nullptr;

		return self;
	}

	template <typename F, WHERE(std::is_convertible<F*, T*>::value)>
	UniquePtr& operator=(NewPtr<F>&& value)
	{
		this->Destroy();
		_controller = value.TakeOwnership();
		_controller->GetRefCounter().SetOwnership(OwnershipType::Unique);

		return self;
	}

	template <typename F, WHERE(!std::is_void<F>::value)>
	explicit operator UniquePtr<F>&() &
	{
		return reinterpret_cast<UniquePtr<F>&>(self);
	}

	template <typename F, WHERE(!std::is_void<F>::value)>
	explicit operator const UniquePtr<F>&() const &
	{
		return reinterpret_cast<const UniquePtr<F>&>(self);
	}

	template <typename F, WHERE(!std::is_void<F>::value)>
	explicit operator UniquePtr<F>&&() const &&
	{
		return reinterpret_cast<UniquePtr<F>&&>(self);
	}

	////////////////
	///   Data   ///
private:

	MemoryBlockController* _controller;
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

	UniquePtr()
		: _controller(nullptr)
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
		: _controller(move._controller)
	{
		move._controller = nullptr;
	}
	~UniquePtr()
	{
		this->Destroy();
	}

	template <typename T>
	UniquePtr(const UniquePtr<T>& copy) = delete;

	template <typename T>
	UniquePtr(UniquePtr<T>&& move)
		: _controller(move._controller)
	{
		move._controller = nullptr;
	}

	template <typename T>
	UniquePtr(NewPtr<T>&& value)
	{
		_controller = value.TakeOwnership();
		_controller->GetRefCounter().SetOwnership(OwnershipType::Unique);
	}

	///////////////////
	///   Methods   ///
public:

	// TODO: Documentation
	FORCEINLINE void* Get()
	{
		return _controller->GetData();
	}

	FORCEINLINE const void* Get() const
	{
		return _controller->GetData();
	}

	FORCEINLINE const TypeInfo& GetValueType() const
	{
		return _controller->GetAllocatedType();
	}

	FORCEINLINE UniquePtr&& Transfer()
	{
		return std::move(self);
	}

	void ToArchive(ArchiveNode& node) const
	{
		if (_controller)
		{
			auto child = node.AddChild(_controller->GetAllocatedType().GetName());
			::ToArchive(*self, *child);
		}
		else
		{
			node.SetValue("null");
		}
	}

private:

	FORCEINLINE void Destroy()
	{
		if (_controller)
		{
			_controller->GetRefCounter().ReleaseOwnerRef();
			_controller->Destroy();
			_controller = nullptr;
		}
	}

	/////////////////////
	///   Operators   ///
public:

	UniquePtr& operator=(std::nullptr_t)
	{
		this->Destroy();
		return self;
	}
	UniquePtr& operator=(const UniquePtr& copy) = delete;
	UniquePtr& operator=(UniquePtr&& move)
	{
		if (this != &move)
		{
			this->Destroy();
			_controller = move._controller;
			move._controller = nullptr;
		}

		return self;
	}
	Variant operator*();
	ImmutableVariant operator*() const;
	operator bool() const
	{
		return _controller != nullptr;
	}
	bool operator==(std::nullptr_t) const
	{
		return _controller == nullptr;
	}
	bool operator!=(std::nullptr_t) const
	{
		return _controller != nullptr;
	}

	template <typename T>
	UniquePtr& operator=(const UniquePtr<T>& copy) = delete;

	template <typename T>
	UniquePtr& operator=(UniquePtr<T>&& move)
	{
		// UniquePtr<void> can never be viewed as another type of UniquePtr, so identity check is not necessary
		this->Destroy();
		_controller = move._controller;
		move._controller = nullptr;

		return self;
	}

	template <typename T>
	UniquePtr& operator=(NewPtr<T>&& move)
	{
		this->Destroy();
		_controller = move.TakeOwnership();
		_controller->GetRefCounter().SetOwnership(OwnershipType::Unique);

		return self;
	}

	////////////////
	///   Data   ///
private:

	MemoryBlockController* _controller;
};

/** Future-proof Alias for 'UniquePtr'. */
template <typename T>
using unique = UniquePtr<T>;

//////////////////////
///   Reflection   ///

template <typename T>
BUILD_TEMPLATE_REFLECTION(UniquePtr, T);
