// EventHandler.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Event/EventHandler.h"

//////////////////////
///   Reflection   ///

STRUCT_REFLECTION(EventHandler)
.AddProperty("Owner", "The type that owns this handler.", &EventHandler::GetOwnerType, nullptr)
.AddProperty("Argument Type", "The type of argument that this handler accepts.", &EventHandler::GetArgType, nullptr);
