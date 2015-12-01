// Component.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Reflection/ClassInfo.h>
#include "../include/Engine/GameObject.h"
#include "../include/Engine/Component.h"
#include "../include/Engine/Scene.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Component);

////////////////////////
///   Constructors   ///

Component::Component()
	: _transform(New<Transform>())
{
	_owner = nullptr;
	_scene = nullptr;
	_id = 0;
}
