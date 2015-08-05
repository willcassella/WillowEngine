// Ghost.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Engine/Scene.h>
#include "../include/ExampleGame/Ghost.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Ghost)
.AddProperty("Slider", "", &Ghost::Slider);

////////////////////////
///   Constructors   ///

Ghost::Ghost(Scene& scene)
	: Base(scene), Slider(self)
{
	scene.Events.Bind("Poof", self, &Ghost::Disappear);
	scene.Events.Bind("Spin", self, &Ghost::Spin);
	hasDisappeared = false;
}

///////////////////
///   Actions   ///

void Ghost::Disappear()
{
	if (!hasDisappeared)
	{
		//MeshComponent.Disable();
		hasDisappeared = true;
	}
	else
	{
		//MeshComponent.Enable();
		hasDisappeared = false;
	}
}

void Ghost::Spin(float value)
{
	Transform.Rotate(Vec3::Up, value);
}