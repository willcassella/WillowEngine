// Camera.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Engine/Camera.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Camera)
.AddField("CameraComponent", &Camera::CameraComponent);

////////////////////////
///   Constructors   ///

Camera::Camera(const String& name)
	: Super(name), CameraComponent(This)
{
	// All done
}