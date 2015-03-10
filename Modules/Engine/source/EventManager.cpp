// EventManager.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Engine/EventManager.h"

////////////////////////
///   Constructors   ///

EventManager::~EventManager()
{
	for (auto& dispatcher : _dispatchers)
	{
		for (auto& handler : dispatcher.Second)
		{
			delete handler;
		}
	}
}

///////////////////
///   Methods   ///

void EventManager::DispatchInputEvent(const String& eventName, float value)
{
	if (_dispatchers.HasKey(eventName))
	{
		for (const auto& i : _dispatchers[eventName])
		{
			i->Dispatch(value);
		}
	}
}