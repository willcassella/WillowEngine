// Camera.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Engine/World.h"
#include "../../include/Engine/GameObjects/Camera.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Camera)
;//.Field("Lens", &Camera::Lens, "");

///////////////////
///   Methods   ///

void Camera::Build()
{
	Base::Build();
	CameraComponent = Attach<class CameraComponent>();
}
