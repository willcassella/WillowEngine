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
	scene.Events.Bind("MoveForward", self, &FPSCamera::MoveForward);
	scene.Events.Bind("MoveRight", self, &FPSCamera::MoveRight);
	scene.Events.Bind("LookUp", self, &FPSCamera::LookUp);
	scene.Events.Bind("LookRight", self, &FPSCamera::LookRight);
}

///////////////////
///   Actions   ///

void FPSCamera::MoveForward(float value)
{
	Transform.Translate(Vec3(0, 0, -value));
}

void FPSCamera::MoveRight(float value)
{
	Transform.Translate(Vec3(value, 0, 0));
}

void FPSCamera::LookUp(float value)
{
	Transform.Rotate(Vec3::Right, value);
}

void FPSCamera::LookRight(float value)
{
	Transform.Rotate(Vec3::Up, value, false);
}