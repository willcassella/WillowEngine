// EventManager.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Containers/Table.h"
#include "../Containers/Queue.h"
#include "EventHandler.h"

struct CORE_API EventManager final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	////////////////////////
	///   Constructors   ///
public:

	EventManager() = default;
	EventManager(const EventManager& copy) = delete;
	EventManager(EventManager&& move) = default;

	///////////////////
	///   Methods   ///
public:

	/** Dispatch an event */
	void DispatchEvent(Event&& event);

	FORCEINLINE void DispatchEvent(const String& name)
	{
		DispatchEvent(Event(name));
	}

	template <typename ArgT>
	FORCEINLINE void DispatchEvent(const String& name, const ArgT& value)
	{
		DispatchEvent(Event(name, value));
	}

	/** Binds the given event handler on the given object to the given event */
	template <class OwnerT, typename HandlerT>
	void Bind(const String& eventName, OwnerT& object, HandlerT handler)
	{
		_handlers[eventName].Add(EventHandler(object, handler));
	}

	/** Dispatches all events in the event queue */
	void Flush();

	/////////////////////
	///   Operators   ///
public:

	EventManager& operator=(const Event& copy) = delete;
	EventManager& operator=(EventManager&& move) = default;

	////////////////
	///   Data   ///
private:

	Table<String, Array<EventHandler>> _handlers;
	Queue<Event> _eventQueue;
};
