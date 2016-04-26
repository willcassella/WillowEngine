// EventHandler.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Event/EventHandler.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/PointerInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(EventHandler);

///////////////////
///   Methods   ///

void EventHandler::invoke(void* object, const void* value) const
{
	this->_handler(object, value);
}
