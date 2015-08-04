// Camera.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Engine/Scene.h"
#include "../../include/Engine/GameObjects/Camera.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Camera)
.AddProperty("Lens", "", &Camera::Lens);

////////////////////////
///   Constructors   ///

Camera::Camera(Scene& scene)
	: Base(scene), Lens(self)
{
	// All done
}