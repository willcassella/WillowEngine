// EventManager.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Event/EventManager.h"
#include "../../include/Core/Reflection/StructInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(EventManager);

///////////////////
///   Methods   ///

void EventManager::DispatchEvent(Event&& event)
{
	_eventQueue.Push(std::move(event));
}

void EventManager::Flush()
{
	_eventQueue.Clear();
}
