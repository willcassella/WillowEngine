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

	/** Returns a pointer to the start of this Buffer, as the given type. */
	template <typename T>
	FORCEINLINE T* GetValueAs()
	{
		return reinterpret_cast<T*>(_value);
	}

	/** Returns a pointer to the start of this Buffer, as the given type. */
	template <typename T>
	FORCEINLINE const T* GetValueAs() const
	{
		return reinterpret_cast<T*>(_value);
	}

	////////////////
	///   Data   ///
private:

	byte _value[Size];
};
