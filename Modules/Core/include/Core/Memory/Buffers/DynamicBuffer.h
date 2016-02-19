// DynamicBuffer.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../../config.h"

struct CORE_API DynamicBuffer final
{
	////////////////////////
	///   Constructors   ///
public:

	DynamicBuffer();
	explicit DynamicBuffer(std::size_t size);
	DynamicBuffer(const DynamicBuffer& copy);
	DynamicBuffer(DynamicBuffer&& move);
	~DynamicBuffer();

	///////////////////
	///   Methods   ///
public:

	/** Returns the size of this DynamicBuffer. */
	FORCEINLINE std::size_t GetSize() const
	{
		return _size;
	}

	/** Returns the alignment of this DynamicBuffer. */
	static constexpr std::size_t GetAlignment()
	{
		return alignof(std::max_align_t);
	}

	/** Returns a pointer to the start of this DynamicBuffer. */
	template <typename T = byte>
	FORCEINLINE T* GetPointer() &
	{
		return reinterpret_cast<T*>(_value);
	}

	/** Returns a pointer to the start of this DynamicBuffer. */
	template <typename T = byte>
	FORCEINLINE const T* GetPointer() const &
	{
		return reinterpret_cast<const T*>(_value);
	}

	/** Resizes this DynamicBuffer, copying existing data. */
	void Resize(std::size_t newSize);

	/** Resizes this DynamicBuffer, erasing existing data. */
	void Reset(std::size_t newSize);

	/////////////////////
	///   Operators   ///
public:

	DynamicBuffer& operator=(const DynamicBuffer& copy);
	DynamicBuffer& operator=(DynamicBuffer&& move);

	////////////////
	///   Data   ///
private:

	byte* _value;
	std::size_t _size;
};
