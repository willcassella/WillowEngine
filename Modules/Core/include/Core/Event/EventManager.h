// EventManager.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <memory>
#include "../Containers/Table.h"
#include "EventHandler.h"

struct EventManager final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;

	///////////////////
	///   Methods   ///
public:

	/** Dispatch an event */
	void DispatchEvent(const Event& event);

	FORCEINLINE void DispatchEvent(const String& name)
	{
		DispatchEvent(TEvent<void>(name));
	}

	template <typename ArgType>
	FORCEINLINE void DispatchEvent(const String& name, const ArgType& value)
	{
		DispatchEvent(TEvent<ArgType>(name, value));
	}

	/** Binds the given event handler on the given object to the given event */
	template <class OwnerType, typename HandlerType>
	void Bind(const String& eventName, OwnerType* object, HandlerType handler)
	{
		_handlers[eventName].Add(EventHandler(object, handler));
	}

	////////////////
	///   Data   ///
private:

	Table<String, Array<EventHandler>> _handlers;
	Queue<Event*> _eventQueue;
};