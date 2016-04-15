// LightComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Engine/Components/Rendering/LightComponent.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::LightComponent)
.Field("color", &LightComponent::color, "The color of this light.")
.Field("intensity", &LightComponent::intensity, "The intensity of this light.");