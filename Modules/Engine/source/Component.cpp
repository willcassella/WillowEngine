// Component.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Reflection/ClassInfo.h>
#include "../include/Engine/Component.h"
#include "../include/Engine/World.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Component)
.Data("Entity", &Component::_entity);

////////////////////////
///   Constructors   ///

Component::Component()
{
	_entity = nullptr;
}
