// Light.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Engine/Scene.h"
#include "../../include/Engine/GameObjects/Light.h"

///////////////////////
///    Reflection   ///

BUILD_REFLECTION(Light)
;//.Field("LightComponent", &Light::LightComponent, "The light.");

///////////////////
///   Methods   ///

void Light::Build()
{
	Base::Build();
	LightComponent = Attach<class LightComponent>();
}
