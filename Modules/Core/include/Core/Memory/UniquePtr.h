// UniquePtr.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Reflection/StructInfo.h"
#include "MemoryManager.h"
#include "../Application.h"

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

	/** Only the 'new' function is allowed to create new UniquePtr values. */
	template <typename F, typename ... Args>
	friend UniquePtr<F> New(Args&& ...);

	////////////////////////
	///   Constructors   ///
public:

	UniquePtr()
		: _header(nullptr)
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
		: _header(move._header)
	{
		move._header = nullptr;
	}
	~UniquePtr()
	{
		self = nullptr;
	}

	template <typename F>
	UniquePtr(const UniquePtr<F>& copy) = delete;

	template <typename F, WHERE(std::is_convertible<F*, T*>::value)>
	UniquePtr(UniquePtr<F>&& move)
		: _header(move._header)
	{
		move._header = nullptr;
	}

private:

	UniquePtr(MemoryBlockHeader* value)
		: _header(value)
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	FORCEINLINE T* Get()
	{
		return (T*)_header->GetData();
	}

	FORCEINLINE const T* Get() const
	{
		return (T*)_header->GetData();
	}

	FORCEINLINE UniquePtr<T>&& Transfer()
	{
		return std::move(self);
	}

	void ToArchive(ArchiveNode& node) const
	{
		if (_header)
		{
			if (std::is_polymorphic<T>::value)
			{
				// Since T is polymorphic, we need to document value's type
				auto child = node.AddChild(_header->GetAllocatedType().GetName());
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

	FORCEINLINE void MarkHeaderForDestruction()
	{
		if (_header)
		{
			_header->MarkForDestruction();
		}
	}

	/////////////////////
	///   Operators   ///
public:
	
	UniquePtr& operator=(std::nullptr_t)
	{
		MarkHeaderForDestruction();
		_header = nullptr;

		return self;
	}
	UniquePtr& operator=(const UniquePtr& copy) = delete;
	UniquePtr& operator=(UniquePtr&& move)
	{
		if (this != &move)
		{
			MarkHeaderForDestruction();
			_header = move._header;
			move._header = nullptr;
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
		return _header != nullptr;
	}

	template <typename F>
	UniquePtr& operator=(const UniquePtr<F>& copy) = delete;

	template <typename F, WHERE(std::is_convertible<F*, T*>::value)>
	UniquePtr& operator=(UniquePtr<F>&& move)
	{
		if (this != &move)
		{
			MarkHeaderForDestruction();
			_header = move._header;
			move._header = nullptr;
		}

		return self;
	}

	////////////////
	///   Data   ///
private:

	MemoryBlockHeader* _header;
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
		: _header(nullptr)
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
		: _header(move._header)
	{
		move._header = nullptr;
	}
	~UniquePtr()
	{
		self = nullptr;
	}

	template <typename T>
	UniquePtr(const UniquePtr<T>& copy) = delete;

	template <typename T>
	UniquePtr(UniquePtr<T>&& move)
		: _header(move._header)
	{
		move._header = nullptr;
	}

	///////////////////
	///   Methods   ///
public:

	// TODO: Documentation
	FORCEINLINE void* Get()
	{
		return _header->GetData();
	}

	FORCEINLINE const void* Get() const
	{
		return _header->GetData();
	}

	FORCEINLINE const TypeInfo& GetValueType() const
	{
		return _header->GetAllocatedType();
	}

	FORCEINLINE UniquePtr&& Transfer()
	{
		return std::move(self);
	}

	void ToArchive(ArchiveNode& node) const
	{
		if (_header)
		{
			auto child = node.AddChild(_header->GetAllocatedType().GetName());
			::ToArchive(*self, *child);
		}
		else
		{
			node.SetValue("null");
		}
	}

private:

	FORCEINLINE void MarkHeaderForDestruction()
	{
		if (_header)
		{
			_header->MarkForDestruction();
		}
	}

	/////////////////////
	///   Operators   ///
public:

	UniquePtr& operator=(std::nullptr_t)
	{
		MarkHeaderForDestruction();
		_header = nullptr;
		return self;
	}
	UniquePtr& operator=(const UniquePtr& copy) = delete;
	UniquePtr& operator=(UniquePtr&& move)
	{
		if (this != &move)
		{
			MarkHeaderForDestruction();
			_header = move._header;
			move._header = nullptr;
		}

		return self;
	}
	Variant operator*();
	ImmutableVariant operator*() const;
	operator bool() const
	{
		return _header != nullptr;
	}

	template <typename T>
	UniquePtr& operator=(const UniquePtr<T>& copy) = delete;

	template <typename F>
	UniquePtr& operator=(UniquePtr<F>&& move)
	{
		// UniquePtr<void> can never be viewed as another type of UniquePtr, so identity check is not necessary
		MarkHeaderForDestruction();
		_header = move._header;
		move._header = nullptr;

		return self;
	}

	////////////////
	///   Data   ///
private:

	MemoryBlockHeader* _header;
};

/////////////////////
///   Functions   ///

/** Constructs a new instance of 'T'. */
template <typename T, typename ... ArgT>
UniquePtr<T> New(ArgT&& ... args)
{
	auto header = Application::GetMemoryManager().AllocateNew(TypeOf<T>());
	new (header->GetData()) T(std::forward<ArgT>(args)...);
	header->Status = MemoryBlockStatus::Valid;

	return header;
}

//////////////////////
///   Reflection   ///

template <typename T>
BUILD_TEMPLATE_REFLECTION(UniquePtr, T);
