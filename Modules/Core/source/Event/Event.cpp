// Event.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Event/Event.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Event)
.AddField("Name", &Event::_name);

CLASS_REFLECTION(TEvent<void>);
