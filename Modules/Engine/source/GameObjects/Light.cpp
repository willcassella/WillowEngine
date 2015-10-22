// Light.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Engine/GameObjects/Light.h"

///////////////////////
///    Reflection   ///

BUILD_REFLECTION(Light)
.Field("LightComponent", &Light::LightComponent, "The light.");

////////////////////////
///   Constructors   ///

Light::Light(Scene& scene)
	: Base(scene)
{
	LightComponent = New<class LightComponent>(self);
}
