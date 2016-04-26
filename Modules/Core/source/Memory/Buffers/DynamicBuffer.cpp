// DynamicBuffer.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <cstdlib>
#include <cstring>
#include "../../../include/Core/Memory/Buffers/DynamicBuffer.h"

////////////////////////
///   Constructors   ///

DynamicBuffer::DynamicBuffer()
	: _buffer{ nullptr }, _size{ 0 }
{
	// All done
}

DynamicBuffer::DynamicBuffer(std::size_t size)
{
	this->_buffer = static_cast<byte*>(std::malloc(size));
	this->_size = size;
}

DynamicBuffer::DynamicBuffer(const DynamicBuffer& copy)
	: DynamicBuffer(copy._size)
{
	std::memcpy(this->_buffer, copy._buffer, copy._size);
}

DynamicBuffer::DynamicBuffer(DynamicBuffer&& move)
{
	this->_buffer = move._buffer;
	this->_size = move._size;

	move._buffer = nullptr;
	move._size = 0;
}

DynamicBuffer::~DynamicBuffer()
{
	std::free(this->_buffer);
}

///////////////////
///   Methods   ///

void DynamicBuffer::resize(std::size_t newSize)
{
	this->_buffer = static_cast<byte*>(std::realloc(this->_buffer, newSize));
	this->_size = newSize;
}

void DynamicBuffer::reset(std::size_t newSize)
{
	std::free(this->_buffer);

	this->_buffer = static_cast<byte*>(std::malloc(newSize));
	this->_size = newSize;
}

void DynamicBuffer::reserve(std::size_t size)
{
	if (this->get_size() < size)
	{
		this->resize(this->get_size() + size);
	}
}

/////////////////////
///   Operators   ///

DynamicBuffer& DynamicBuffer::operator=(const DynamicBuffer& copy)
{
	if (this != &copy)
	{
		this->reset(copy._size);
		std::memcpy(this->_buffer, copy._buffer, copy._size);
	}

	return *this;
}

DynamicBuffer& DynamicBuffer::operator=(DynamicBuffer&& move)
{
	if (this != &move)
	{
		std::free(this->_buffer);

		this->_buffer = move._buffer;
		this->_size = move._size;

		move._buffer = nullptr;
		move._size = 0;
	}

	return *this;
}
