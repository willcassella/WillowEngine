// Event.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Event/Event.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Event)
.AddProperty("Name", "", &Event::_name, nullptr)
.AddProperty("Argument Type", "", &Event::GetArgType, nullptr);

CLASS_REFLECTION(TEvent<void>);
