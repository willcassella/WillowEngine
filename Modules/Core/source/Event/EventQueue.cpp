// EventQueue.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Event/EventQueue.h"
#include "../../include/Core/Reflection/StructInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(EventQueue);

////////////////////////
///   Constructors   ///

EventQueue::EventQueue()
	: _next_value_offset{ 0 }
{
	// All done
}

EventQueue::EventQueue(const EventQueue& copy)
	: _next_value_offset{ copy._next_value_offset }
{
	copy.copy_values(this->_buffer);
	this->_events = copy._events;
}

EventQueue::EventQueue(EventQueue&& move)
	: _events(std::move(move._events)),
	_next_value_offset{ move._next_value_offset },
	_buffer{ std::move(move._buffer) }
{
	move._next_value_offset = 0;
}

EventQueue::~EventQueue()
{
	this->destroy_values();
}

///////////////////
///   Methods   ///

void EventQueue::push_event(String name)
{
	this->_events.Add(std::make_pair(std::move(name), nullptr));
}

void EventQueue::clear()
{
	this->destroy_values();
	this->_events.Clear();
	this->_next_value_offset = 0;
}

void EventQueue::copy_values(DynamicBuffer& target) const
{
	// Reserve space
	target.reserve(this->_buffer.get_size());
	
	// Get starting pointer and offset
	byte* const start = target.get_pointer();
	std::size_t offset = 0;

	// Copy all values into target buffer
	this->enumerate_values([start, &offset](const TypeInfo& type, const void* value)
	{
		// Compute offset for given value in target buffer
		offset = align_offset(offset, type.get_alignment());

		// Copy it into the buffer
		type.get_copy_constructor()(start + offset, value);
		
		// Increment the offset
		offset += type.get_size();
	});
}

void EventQueue::move_and_destroy_values(DynamicBuffer& target)
{
	// Reserve space
	target.reserve(_buffer.get_size());
	
	// Get starting pointer and offset
	byte* const start = target.get_pointer();
	std::size_t offset = 0;

	this->enumerate_values([start, &offset](const TypeInfo& type, void* value)
	{
		// Compute offset for given value in target buffer
		offset = align_offset(offset, type.get_alignment());

		// Copy it into the buffer
		type.get_move_constructor()(start + offset, value);

		// Destroy the old value
		type.get_destructor()(value);

		// Increment the offset
		offset += type.get_size();
	});
}

void EventQueue::destroy_values()
{
	this->enumerate_values([](const TypeInfo& type, void* value)
	{
		type.get_destructor()(value);
	});
}

/////////////////////
///   Operators   ///

EventQueue& EventQueue::operator=(const EventQueue& copy)
{
	if (this != &copy)
	{
		// Destroy values in this EventQueue
		this->destroy_values();

		this->_events = copy._events;
		this->_next_value_offset = copy._next_value_offset;
		copy.copy_values(this->_buffer);
	}

	return *this;
}

EventQueue& EventQueue::operator=(EventQueue&& move)
{
	if (this != &move)
	{
		this->destroy_values();

		this->_events = std::move(move._events);
		this->_next_value_offset = move._next_value_offset;
		this->_buffer = std::move(move._buffer);

		move._next_value_offset = 0;
	}

	return *this;
}
