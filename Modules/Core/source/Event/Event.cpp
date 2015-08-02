// Event.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Event/Event.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/VoidInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Event)
.AddProperty("Name", "", &Event::_name, nullptr)
.AddProperty("Argument Type", "", &Event::GetArgType, nullptr);

////////////////////////
///   Constructors   ///

Event::Event(const String& name)
	: _name(name), _argType(TypeOf<void>())
{
	// All done
}
