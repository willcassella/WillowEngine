// CameraComponent.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Engine/Scene.h"
#include "../../include/Engine/GameObject.h"
#include "../../include/Engine/Components/CameraComponent.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(CameraComponent)
.AddProperty("HFov", "The horizontal field of view of the camera.", &CameraComponent::HFov)
.AddProperty("VFov", "The vertical field of view of the camera.", &CameraComponent::VFov)
.AddProperty("ZMin", "The distance to the near clipping plane.", &CameraComponent::ZMin)
.AddProperty("ZMax", "The distance to the far clipping plane.", &CameraComponent::ZMax);
