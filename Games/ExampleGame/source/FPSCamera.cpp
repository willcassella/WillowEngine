// FPSCamera.cpp

#include <Engine/World.h>
#include "../include/ExampleGame/FPSCamera.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(FPSCamera);

///////////////////
///   Methods   ///

void FPSCamera::OnSpawn()
{
	Base::OnSpawn();

	GetWorld().Events.Bind("Move", self, &FPSCamera::Move);
	GetWorld().Events.Bind("Look", self, &FPSCamera::Look);
	GetWorld().Events.Bind("Click", self, &FPSCamera::Click);
}

///////////////////
///   Actions   ///

void FPSCamera::Move(Vec2 direction)
{
	Translate(Vec3(direction.X, 0, -direction.Y)/10);
}

void FPSCamera::Look(Vec2 direction)
{
	RotateGlobal(Vec3::Up, direction.X);
	Rotate(Vec3::Right, direction.Y);
}

void FPSCamera::Click()
{
	// Spawn something
}
