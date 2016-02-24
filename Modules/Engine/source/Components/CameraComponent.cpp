// CameraComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Engine/World.h"
#include "../../include/Engine/Components/CameraComponent.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::CameraComponent)
.Field("HFov", &CameraComponent::Fov, "The horizontal field of view of the camera.")
.Field("VFov", &CameraComponent::ScreenRatio, "The screen ratio of this camera.")
.Field("ZMin", &CameraComponent::ZMin, "The distance to the near clipping plane.")
.Field("ZMax", &CameraComponent::ZMax, "The distance to the far clipping plane.");
