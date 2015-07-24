// StaticBuffer.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"

template <uint32 Size>
struct StaticBuffer final
{
	///////////////////
	///   Methods   ///
public:

	/** Returns the size of this Buffer (in case you forgot). */
	constexpr uint32 GetSize() const
	{
		return Size;
	}

	/** Returns a pointer to the start of this Buffer. */
	FORCEINLINE byte* GetValue()
	{
		return _value;
	}

	/** Returns a pointer to the start of this Buffer. */
	FORCEINLINE const byte* GetValue() const
	{
		return _value;
	}

	////////////////
	///   Data   ///
private:

	byte _value[Size];
};
