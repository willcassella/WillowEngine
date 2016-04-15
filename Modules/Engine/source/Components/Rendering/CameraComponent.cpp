// CameraComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Engine/World.h"
#include "../../../include/Engine/Components/Rendering/CameraComponent.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::CameraComponent)
.Field("HFov", &CameraComponent::fov, "The horizontal field of view of the camera.")
.Field("z_min", &CameraComponent::z_min, "The distance to the near clipping plane.")
.Field("z_max", &CameraComponent::z_max, "The distance to the far clipping plane.");
