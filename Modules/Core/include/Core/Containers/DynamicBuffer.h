// DynamicBuffer.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"

struct CORE_API DynamicBuffer final
{
	////////////////////////
	///   Constructors   ///
public:

	DynamicBuffer();
	explicit DynamicBuffer(uint32 size);
	DynamicBuffer(const DynamicBuffer& copy);
	DynamicBuffer(DynamicBuffer&& move);
	~DynamicBuffer();

	///////////////////
	///   Methods   ///
public:

	/** Returns the size of this DynamicBuffer. */
	FORCEINLINE uint32 GetSize() const
	{
		return _size;
	}

	/** Returns a pointer to the start of this DynamicBuffer. */
	FORCEINLINE byte* GetValue()
	{
		return _value;
	}

	/** Returns a pointer to the start of this DynamicBuffer. */
	FORCEINLINE const byte* GetValue() const
	{
		return _value;
	}

	/** Resizes this DynamicBuffer, copying existing data. */
	void Resize(uint32 newSize);

	/** Resizes this DynamicBuffer, erasing existing data. */
	void Reset(uint32 newSize);

	/** Returns a pointer to the start of this DynamicBuffer, as the given type. */
	template <typename T>
	FORCEINLINE T* GetValueAs()
	{
		return reinterpret_cast<T*>(_value);
	}

	/** Returns a pointer to the start of this DynamicBuffer, as the given type. */
	template <typename T>
	FORCEINLINE const T* GetValueAs() const
	{
		return reinterpret_cast<const T*>(_value);
	}

	/////////////////////
	///   Operators   ///
public:

	DynamicBuffer& operator=(const DynamicBuffer& copy);
	DynamicBuffer& operator=(DynamicBuffer&& move);

	////////////////
	///   Data   ///
private:

	uint32 _size;
	byte* _value;
};
