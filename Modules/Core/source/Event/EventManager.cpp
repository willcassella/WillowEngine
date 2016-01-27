// EventManager.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Event/EventManager.h"
#include "../../include/Core/Reflection/StructInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(EventManager)
.Data("Handlers", &EventManager::_handlers)
.Data("EventQueue", &EventManager::_eventQueue);

///////////////////
///   Methods   ///

void EventManager::DispatchEvent(Event&& event)
{
	_eventQueue.Push(std::move(event));
}

void EventManager::Flush()
{
	while (!_eventQueue.IsEmpty())
	{
		auto event = _eventQueue.Pop();
		
		// If we have a handler for this event
		if (auto handlers = _handlers.Find(event.GetName()))
		{
			for (const auto& handler : *handlers)
			{
				handler.TryHandle(event);
			}
		}
	}
}
