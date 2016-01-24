// LightComponent.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Engine/Components/LightComponent.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(LightComponent)
.Field("Color", &LightComponent::Color, "The color of this light.")
.Field("Intensity", &LightComponent::Intensity, "The intensity of this light.");