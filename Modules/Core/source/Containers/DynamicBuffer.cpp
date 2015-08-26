// DynamicBuffer.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <cstdlib>
#include <cstring>
#include "../../include/Core/Containers/DynamicBuffer.h"

////////////////////////
///   Constructors   ///

DynamicBuffer::DynamicBuffer()
	: _size(0), _value(nullptr)
{
	// All done
}

DynamicBuffer::DynamicBuffer(uint32 size)
{
	_size = size;
	_value = (byte*)malloc(size);
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

void DynamicBuffer::Resize(uint32 newSize)
{
	_size = newSize;
	_value = (byte*)realloc(_value, newSize);
}

void DynamicBuffer::Reset(uint32 newSize)
{
	free(_value);

	_size = newSize;
	_value = (byte*)malloc(newSize);
}

/////////////////////
///   Operators   ///

DynamicBuffer& DynamicBuffer::operator=(const DynamicBuffer& copy)
{
	if (this != &copy)
	{
		Reset(copy._size);
		memcpy(_value, copy._value, copy._size);
	}

	return self;
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

	return self;
}
