// CameraComponent.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Math/Mat4.h>
#include "../include/Engine/CameraComponent.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(CameraComponent)
.AddField("HFOV", &CameraComponent::HFOV)
.AddField("VFOV", &CameraComponent::VFOV)
.AddField("ZMin", &CameraComponent::ZMin)
.AddField("ZMax", &CameraComponent::ZMax);

////////////////////////
///   Constructors   ///

CameraComponent::CameraComponent(GameObject& owner)
	: Super(owner)
{
	// All done
}