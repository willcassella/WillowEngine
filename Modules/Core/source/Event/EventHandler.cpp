// EventHandler.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Event/EventHandler.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(EventHandler)
.AddProperty("Owner", "The type that owns this handler.", &EventHandler::GetOwnerType, nullptr)
.AddProperty("Argument Type", "The type of argument that this handler accepts.", &EventHandler::GetArgType, nullptr);

///////////////////
///   Methods   ///

void EventHandler::TryHandle(const Event& event) const
{
	if (event.GetArgType().IsCastableTo(_argType))
	{
		_handler(event);
	}
}
