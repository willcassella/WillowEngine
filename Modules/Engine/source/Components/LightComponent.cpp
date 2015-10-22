// LightComponent.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Engine/Components/LightComponent.h"
#include "../../include/Engine/GameObject.h"

//////////////////////
///   Reflection   ///

BUILD_ENUM_REFLECTION(LightType)
.Value("Point", LightType::Point)
.Value("Spot", LightType::Spot)
.Value("Directional", LightType::Directional);

BUILD_REFLECTION(LightComponent)
.Field("Color", &LightComponent::Color, "The color of this light.")
.Field("Radius", &LightComponent::Radius, "The radius of this light.")
.Field("Intensity", &LightComponent::Intensity, "The intensity of this light.")
.Field("Type", &LightComponent::Type, "The type of light this is.");