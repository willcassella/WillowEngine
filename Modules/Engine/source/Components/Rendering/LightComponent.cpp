// LightComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Engine/Components/Rendering/LightComponent.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::LightComponent)
.Field("Color", &LightComponent::Color, "The color of this light.")
.Field("Intensity", &LightComponent::Intensity, "The intensity of this light.");