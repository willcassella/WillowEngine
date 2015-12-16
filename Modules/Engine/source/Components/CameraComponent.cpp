// CameraComponent.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Engine/World.h"
#include "../../include/Engine/GameObject.h"
#include "../../include/Engine/Components/CameraComponent.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(CameraComponent)
.Field("HFov", &CameraComponent::HFov, "The horizontal field of view of the camera.")
.Field("VFov", &CameraComponent::VFov, "The vertical field of view of the camera.")
.Field("ZMin", &CameraComponent::ZMin, "The distance to the near clipping plane.")
.Field("ZMax", &CameraComponent::ZMax, "The distance to the far clipping plane.");
