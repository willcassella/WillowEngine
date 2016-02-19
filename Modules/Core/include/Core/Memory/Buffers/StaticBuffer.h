// StaticBuffer.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <new>
#include <utility>
#include "../../env.h"

/** Object containing a statically-sized buffer, for various purposes. */
template <std::size_t Size, std::size_t Alignment = alignof(std::max_align_t)>
struct StaticBuffer final
{
	///////////////////
	///   Methods   ///
public:

	/** Returns the size of this Buffer (in case you forgot). */
	static constexpr std::size_t GetSize()
	{
		return Size;
	}

	/** Returns the alignment of this Buffer (in case you forgot). */
	static constexpr std::size_t GetAlignment()
	{
		return Alignment;
	}

	/** Returns a pointer to the start of this Buffer, as the given type. */
	template <typename T = byte>
	FORCEINLINE T* GetPointer() &
	{
		CheckStorage<T>();
		return reinterpret_cast<T*>(_buffer);
	}

	/** Returns a pointer to the start of this Buffer, as the given type. */
	template <typename T = byte>
	FORCEINLINE const T* GetPointer() const &
	{
		CheckStorage<T>();
		return reinterpret_cast<const T*>(_buffer);
	}

	/** Uses placement new to construct an instance of the given type in this StaticBuffer. */
	template <typename T, typename ... Args>
	FORCEINLINE T* Emplace(Args&& ... args) &
	{
		CheckStorage<T>();
		return new (_buffer) T(std::forward<Args>(args)...);
	}

private:

	/** Asserts that this StaticBuffer meets the storage requirements to contain an instance of T. */
	template <typename T>
	static void CheckStorage()
	{
		static_assert(sizeof(T) <= Size, "This StaticBuffer is not large enough to contain the given value.");
		static_assert(alignof(T&) <= Alignment, "THis StaticBuffer is not aligned properly to contain the given type.");
	}

	////////////////
	///   Data   ///
private:

	alignas(Alignment) byte _buffer[Size];
};

template <typename T>
using StaticBufferFor = StaticBuffer<sizeof(T), alignof(T)>;
