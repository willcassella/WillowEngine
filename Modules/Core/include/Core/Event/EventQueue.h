// EventQueue.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <memory>
#include <utility>
#include "../config.h"
#include "../Memory/Buffers/DynamicBuffer.h"
#include "../Memory/Functions.h"
#include "../Containers/Array.h"
#include "../Reflection/TypeInfo.h"

struct CORE_API EventQueue final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	////////////////////////
	///   Constructors   ///
public:

	EventQueue();
	EventQueue(const EventQueue& copy);
	EventQueue(EventQueue&& move);
	~EventQueue();

	///////////////////
	///   Methods   ///
public:

	/** Pushes an event without any arguments into this EventQueue. */
	void push_event(String name);

	/** Pushes an event with the given name and argument into this EventQueue. */
	template <typename T>
	void push_event(String name, T value)
	{
		static_assert(Operations::CopyConstruct<T>::Supported, "Event arguments must be copyable.");
		static_assert(Operations::MoveConstruct<T>::Supported, "Event arguments must be moveable.");
		static_assert(Operations::Destroy<T>::Supported, "Event arguments must be destructible.");

		// Compute offset for new value
		_next_value_offset = align_offset(_next_value_offset, alignof(T&));
		
		// Make sure space exists in buffer for new value
		if (_next_value_offset + sizeof(T) > _buffer.get_size())
		{
			// Create a new buffer that is either twice the size of the old buffer, or the size of the old buffer + the requirements for the new value
			const std::size_t nextSize = std::max(_buffer.get_size() * 2, _next_value_offset + sizeof(T));
			DynamicBuffer newBuffer{ nextSize };

			// Move the existing values into the new buffer
			this->move_and_destroy_values(newBuffer);
			this->_buffer = std::move(newBuffer);
		}

		// Create the new value
		new (_buffer.get_pointer() + _next_value_offset) T{ std::move(value) };
		_next_value_offset += sizeof(T);

		// Add the event for this value
		_events.Add(std::make_pair(std::move(name), &TypeOf<T>()));
	}

	/** Clears this EventQueue. */
	void clear();

	/** Enumerates all events in this EventQueue.
	* NOTE: The passed function should accept the arguments: 'const String&', 'const TypeInfo*', 'const void*'.*/
	template <typename F>
	void enumerate(F&& func) const
	{
		const auto* const start = _buffer.get_pointer();
		std::size_t offset = 0;

		for (const auto& event : _events)
		{
			// If the event has an associated value
			if (event.second != nullptr)
			{
				// Compute the offset
				offset = align_offset(offset, event.second->get_alignment());

				// Call the function
				func(event.first, event.second, start + offset);

				// Increment the offset
				offset += event.second->get_size();
			}
			else
			{
				// Call the function
				func(event.first, nullptr, nullptr);
			}
		}
	}

private:

	/** Copies the values in this EventQueue into the given DynamicBuffer. */
	void copy_values(DynamicBuffer& target) const;

	/** Moves the values in this EventQueue into the given DynamicBuffer, and destroys the old ones. */
	void move_and_destroy_values(DynamicBuffer& target);

	/** Destroys all the values in this EventQueue. */
	void destroy_values();

	/** Enumerates over all values in this EventQueue.
	* 'func' - a function accepting a 'const TypeInfo&' and 'void*' arguments, denoting the type of the value and the value itself. */
	template <typename F>
	void enumerate_values(F&& func)
	{
		byte* const start = _buffer.get_pointer();
		std::size_t offset = 0;
		
		for (const auto& event : _events)
		{
			if (event.second != nullptr)
			{
				// Compute offset
				offset = align_offset(offset, event.second->get_alignment());
				
				// Call the function
				func(*event.second, start + offset);
				
				// Increment the offset
				offset += event.second->get_size();
			}
		}
	}

	/** Enumerates over all values in this EventQueue.
	* 'func' - a function accepting a 'const TypeInfo&' and 'const void*' arguments, denoting the type of the value and the value itself. */
	template <typename F>
	void enumerate_values(F&& func) const
	{
		const byte* const start = _buffer.get_pointer();
		std::size_t offset = 0;

		for (const auto& event : _events)
		{
			if (event.second != nullptr)
			{
				// Compute the offset
				offset = align_offset(offset, event.second->get_alignment());

				// Call the function
				func(*event.second, start + offset);
				
				// Increment the next offset
				offset += event.second->get_size();
			}
		}
	}

	/////////////////////
	///   Operators   ///
public:

	EventQueue& operator=(const EventQueue& copy);
	EventQueue& operator=(EventQueue&& move);

	////////////////
	///   Data   ///
private:

	Array<std::pair<String, const TypeInfo*>> _events;
	std::size_t _next_value_offset;
	DynamicBuffer _buffer;
};
