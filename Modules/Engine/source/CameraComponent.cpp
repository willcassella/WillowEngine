// CameraComponent.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Math/Mat4.h>
#include "../include/Engine/CameraComponent.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(CameraComponent)
.AddProperty("HFOV", "The horizontal field of view of the camera.", &CameraComponent::HFOV)
.AddProperty("VFOV", "The vertical field of view of the camera.", &CameraComponent::VFOV)
.AddProperty("ZMin", "The distance to the near clipping plane.", &CameraComponent::ZMin)
.AddProperty("ZMax", "The distance to the far clipping plane.", &CameraComponent::ZMax);

////////////////////////
///   Constructors   ///

CameraComponent::CameraComponent(GameObject& owner)
	: Super(owner)
{
	// All done
}