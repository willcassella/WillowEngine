// FPSCamera.cpp

#include <Engine/Scene.h>
#include "../include/ExampleGame/FPSCamera.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(FPSCamera);

///////////////////
///   Methods   ///

void FPSCamera::OnSpawn()
{
	Base::OnSpawn();

	GetScene().Events.Bind("Move", self, &FPSCamera::Move);
	GetScene().Events.Bind("Look", self, &FPSCamera::Look);
	GetScene().Events.Bind("Click", self, &FPSCamera::Click);
}

///////////////////
///   Actions   ///

void FPSCamera::Move(Vec2 direction)
{
	GetTransform()->Translate(Vec3(direction.X, 0, -direction.Y)/10);
}

void FPSCamera::Look(Vec2 direction)
{
	GetTransform()->Rotate(Vec3::Up, direction.X, false);
	GetTransform()->Rotate(Vec3::Right, direction.Y, true);
}

void FPSCamera::Click()
{
	// Spawn something
}
