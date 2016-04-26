// DynamicBuffer.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <memory>
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
	FORCEINLINE std::size_t get_size() const
	{
		return _size;
	}

	/** Returns the alignment of this DynamicBuffer. */
	static constexpr std::size_t get_alignment()
	{
		return alignof(std::max_align_t);
	}

	/** Returns a pointer to the start of this DynamicBuffer. */
	template <typename T = byte>
	FORCEINLINE T* get_pointer() &
	{
		return reinterpret_cast<T*>(_buffer);
	}

	/** Returns a pointer to the start of this DynamicBuffer. */
	template <typename T = byte>
	FORCEINLINE const T* get_pointer() const &
	{
		return reinterpret_cast<const T*>(_buffer);
	}

	/** Returns a pointer aligned for the given type 'T'.
	* 'start' - The offset within this Buffer to search for space at.
	* 'outEnd' - If space is found, set to the offset within this buffer where the value will end.
	* returns a pointer to aligned storage for the given type, or 'null' if this Buffer cannot meet the requirements. */
	template <typename T>
	T* get_aligned_pointer(std::size_t start, std::size_t& outEnd) &
	{
		if (start >= this->get_size())
		{
			// This buffer can't possibly hold the given type.
			return nullptr;
		}

		void* ptr = this->get_pointer() + start;
		auto space = this->get_size() - start;
		
		if (std::align(alignof(T&), sizeof(T), ptr, space))
		{
			outEnd = reinterpret_cast<std::size_t>(ptr + sizeof(T));
			return static_cast<T*>(ptr);
		}
		else
		{
			return nullptr;
		}
	}

	/** Resizes this DynamicBuffer, copying existing data. */
	void resize(std::size_t newSize);

	/** Resizes this DynamicBuffer, erasing existing data. */
	void reset(std::size_t newSize);

	/** Ensures that this Buffer has at least as much space as the given size.
	* NOTE: If this buffer has less space, this uses "Resize" to acquire more. */
	void reserve(std::size_t size);

	/////////////////////
	///   Operators   ///
public:

	DynamicBuffer& operator=(const DynamicBuffer& copy);
	DynamicBuffer& operator=(DynamicBuffer&& move);

	////////////////
	///   Data   ///
private:

	byte* _buffer;
	std::size_t _size;
};
