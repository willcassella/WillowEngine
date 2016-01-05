// EventHandler.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Event/EventHandler.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/PointerInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(EventHandler)
.Property("Owner", &EventHandler::_ownerType, nullptr, "The type that owns this handler.")
.Property("Argument Type", &EventHandler::_argType, nullptr, "The type of argument that this handler accepts.");

///////////////////
///   Methods   ///

void EventHandler::TryHandle(const Event& event) const
{
	if (event.GetArgType().IsCastableTo(_argType))
	{
		_handler(event);
	}
}
