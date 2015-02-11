// FPSCamera.cpp

#include "..\include\ExampleGame\FPSCamera.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(FPSCamera);

////////////////////////
///   Constructors   ///

FPSCamera::FPSCamera(const String& name, float vFOV, float ratio, float zMin, float zMax)
	: Super(name, vFOV, ratio, zMin, zMax)
{
	EventManager.BindAxis("MoveForward", this, &FPSCamera::MoveForward);
	EventManager.BindAxis("MoveRight", this, &FPSCamera::MoveRight);
	EventManager.BindAxis("LookUp", this, &FPSCamera::LookUp);
	EventManager.BindAxis("LookRight", this, &FPSCamera::LookRight);
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