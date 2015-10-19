// Ghost.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Engine/Scene.h>
#include "../include/ExampleGame/Ghost.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Ghost)
.Field("Slider", &Ghost::Slider, "");

////////////////////////
///   Constructors   ///

Ghost::Ghost(Scene& scene)
	: Base(scene)
{
	Slider = New<SlideComponent>(self);
	MeshComponent = New<StaticMeshComponent>(self);

	scene.Events.Bind("Poof", self, &Ghost::Disappear);
	scene.Events.Bind("Spin", self, &Ghost::Spin);
}

///////////////////
///   Actions   ///

void Ghost::Disappear()
{
	MeshComponent->Visible = !MeshComponent->Visible;
}

void Ghost::Spin(float value)
{
	Transform.Rotate(Vec3::Up, value/10);
}