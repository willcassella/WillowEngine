// DynamicBuffer.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <cstdlib>
#include <cstring>
#include "../../../include/Core/Memory/Buffers/DynamicBuffer.h"

////////////////////////
///   Constructors   ///

DynamicBuffer::DynamicBuffer()
	: _size(0), _value(nullptr)
{
	// All done
}

DynamicBuffer::DynamicBuffer(std::size_t size)
{
	_size = size;
	_value = static_cast<byte*>(malloc(size));
}

DynamicBuffer::DynamicBuffer(const DynamicBuffer& copy)
	: DynamicBuffer(copy._size)
{
	memcpy(_value, copy._value, copy._size);
}

DynamicBuffer::DynamicBuffer(DynamicBuffer&& move)
{
	_size = move._size;
	_value = move._value;

	move._size = 0;
	move._value = nullptr;
}

DynamicBuffer::~DynamicBuffer()
{
	free(_value);
}

///////////////////
///   Methods   ///

void DynamicBuffer::Resize(std::size_t newSize)
{
	_size = newSize;
	_value = static_cast<byte*>(realloc(_value, newSize));
}

void DynamicBuffer::Reset(std::size_t newSize)
{
	free(_value);

	_size = newSize;
	_value = static_cast<byte*>(malloc(newSize));
}

/////////////////////
///   Operators   ///

DynamicBuffer& DynamicBuffer::operator=(const DynamicBuffer& copy)
{
	if (this != &copy)
	{
		this->Reset(copy._size);
		memcpy(_value, copy._value, copy._size);
	}

	return *this;
}

DynamicBuffer& DynamicBuffer::operator=(DynamicBuffer&& move)
{
	if (this != &move)
	{
		free(_value);

		_size = move._size;
		_value = move._value;

		move._size = 0;
		move._value = nullptr;
	}

	return *this;
}
