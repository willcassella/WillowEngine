// DynamicBuffer.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <cstdlib>
#include <cstring>
#include "../../../include/Core/Memory/Buffers/DynamicBuffer.h"

////////////////////////
///   Constructors   ///

DynamicBuffer::DynamicBuffer()
	: _buffer(nullptr), _size(0)
{
	// All done
}

DynamicBuffer::DynamicBuffer(std::size_t size)
{
	_buffer = static_cast<byte*>(std::malloc(size));
	_size = size;
}

DynamicBuffer::DynamicBuffer(const DynamicBuffer& copy)
	: DynamicBuffer(copy._size)
{
	std::memcpy(_buffer, copy._buffer, copy._size);
}

DynamicBuffer::DynamicBuffer(DynamicBuffer&& move)
{
	_buffer = move._buffer;
	_size = move._size;

	move._buffer = nullptr;
	move._size = 0;
}

DynamicBuffer::~DynamicBuffer()
{
	std::free(_buffer);
}

///////////////////
///   Methods   ///

void DynamicBuffer::Resize(std::size_t newSize)
{
	_buffer = static_cast<byte*>(std::realloc(_buffer, newSize));
	_size = newSize;
}

void DynamicBuffer::Reset(std::size_t newSize)
{
	std::free(_buffer);

	_buffer = static_cast<byte*>(std::malloc(newSize));
	_size = newSize;
}

void DynamicBuffer::Reserve(std::size_t size)
{
	if (this->GetSize() < size)
	{
		this->Resize(this ->GetSize() + size);
	}
}

/////////////////////
///   Operators   ///

DynamicBuffer& DynamicBuffer::operator=(const DynamicBuffer& copy)
{
	if (this != &copy)
	{
		this->Reset(copy._size);
		std::memcpy(_buffer, copy._buffer, copy._size);
	}

	return *this;
}

DynamicBuffer& DynamicBuffer::operator=(DynamicBuffer&& move)
{
	if (this != &move)
	{
		std::free(_buffer);

		_buffer = move._buffer;
		_size = move._size;

		move._buffer = nullptr;
		move._size = 0;
	}

	return *this;
}
