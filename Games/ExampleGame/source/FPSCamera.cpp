// FPSCamera.cpp

#include <Engine/Scene.h>
#include "../include/ExampleGame/FPSCamera.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(FPSCamera);

////////////////////////
///   Constructors   ///

FPSCamera::FPSCamera(Scene& scene)
	: Super(scene)
{
	scene.Events.Bind("Move", self, &FPSCamera::Move);
	scene.Events.Bind("Look", self, &FPSCamera::Look);
}

///////////////////
///   Actions   ///

void FPSCamera::Move(Vec2 direction)
{
	Transform.Translate(Vec3(direction.X, 0, direction.Y));
}

void FPSCamera::Look(Vec2 direction)
{
	Transform.Rotate(Vec3::Up, direction.X, false); // TODO: This
}