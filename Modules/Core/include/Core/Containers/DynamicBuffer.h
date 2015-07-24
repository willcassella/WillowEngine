// DynamicBuffer.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"

struct CORE_API DynamicBuffer final
{
	////////////////////////
	///   Constructors   ///
public:

	DynamicBuffer();
	DynamicBuffer(uint32 size);
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

	/** Resizes this buffer, copying existing data. */
	FORCEINLINE void Resize(uint32 newSize);

	/** Resizes this DynamicBuffer, erasing existing data. */
	FORCEINLINE void Reset(uint32 newSize);

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
