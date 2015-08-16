// EventHandler.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Event/EventHandler.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/PointerInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(EventHandler)
.AddProperty("Owner", "The type that owns this handler.", &EventHandler::_ownerType)
.AddProperty("Argument Type", "The type of argument that this handler accepts.", &EventHandler::_argType);

///////////////////
///   Methods   ///

void EventHandler::TryHandle(const Event& event) const
{
	if (event.GetArgType().IsCastableTo(_argType))
	{
		_handler(event);
	}
}
