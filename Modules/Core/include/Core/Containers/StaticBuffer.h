// StaticBuffer.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
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

	/** Returns a pointer to the start of this Buffer, as the given type. */
	template <typename T = byte>
	FORCEINLINE T* GetPointer() &
	{
		return reinterpret_cast<T*>(_value);
	}

	/** Returns a pointer to the start of this Buffer, as the given type. */
	template <typename T = byte>
	FORCEINLINE const T* GetPointer() const &
	{
		return reinterpret_cast<const T*>(_value);
	}

	/** Uses placement new to construct an instance of the given type in this StaticBuffer. */
	template <typename T, typename ... Args>
	T& PlaceValue(Args&& ... args) &
	{
		static_assert(sizeof(T) <= Size, "This StaticBuffer is not large enough to contain the given value.");
		return *new (_value) T(std::forward<Args>(args)...);
	}

	////////////////
	///   Data   ///
private:

	byte _value[Size];
};
