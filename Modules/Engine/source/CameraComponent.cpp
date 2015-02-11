// CameraComponent.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "..\include\Engine\CameraComponent.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(CameraComponent)
.AddField("VFOV", &CameraComponent::VFOV)
.AddField("Ratio", &CameraComponent::Ratio)
.AddField("ZMin", &CameraComponent::ZMin)
.AddField("ZMax", &CameraComponent::ZMax);

////////////////////////
///   Constructors   ///

CameraComponent::CameraComponent(GameObject& owner)
	: Super(owner)
{
	// All done!
}

///////////////////
///   Methods   ///

Mat4 CameraComponent::GetPerspective() const
{
	return Mat4::PerspectiveVFOV(VFOV, Ratio, ZMin, ZMax);
}