// Camera.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Engine/Camera.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Camera)
.AddProperty("Lens", "", &Camera::Lens);

////////////////////////
///   Constructors   ///

Camera::Camera(Scene& scene)
	: Super(scene), Lens(self)
{
	// All done
}