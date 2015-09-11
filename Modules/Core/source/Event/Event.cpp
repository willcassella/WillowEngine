// Event.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Event/Event.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/VoidInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Event)
.Data("Name", &Event::_name)
.Data("Value", &Event::_value)
.Property("Name", &Event::GetName, nullptr, "The name of this event.")
;//.Property("Value", &Event::GetValue, nullptr, "The value associated with this event.");

////////////////////////
///   Constructors   ///

Event::Event(String name)
	: _name(std::move(name))
{
	// All done
}
