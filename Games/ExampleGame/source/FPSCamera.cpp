// FPSCamera.cpp

#include <Engine/Scene.h>
#include "../include/ExampleGame/FPSCamera.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(FPSCamera);

////////////////////////
///   Constructors   ///

FPSCamera::FPSCamera(Scene& scene)
	: Base(scene)
{
	scene.Events.Bind("Move", self, &FPSCamera::Move);
	scene.Events.Bind("Look", self, &FPSCamera::Look);
}

///////////////////
///   Actions   ///

void FPSCamera::Move(Vec2 direction)
{
	Transform.Translate(Vec3(direction.X, 0, -direction.Y)/10);
}

void FPSCamera::Look(Vec2 direction)
{
	Transform.Rotate(Vec3::Up, direction.X, false);
	Transform.Rotate(Vec3::Right, direction.Y, true);
}