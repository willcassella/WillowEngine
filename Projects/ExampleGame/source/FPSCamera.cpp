// FPSCamera.cpp

#include "..\include\ExampleGame\FPSCamera.h"
using namespace ExampleGame;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(ExampleGame::FPSCamera)
HAS_FACTORY
END_REFLECTION_INFO

////////////////////////
///   Constructors   ///

FPSCamera::FPSCamera(const Willow::String& name, float vFOV, float ratio, float zMin, float zMax)
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
	this->Transform.Translate(Willow::Vec3(0, 0, -value));
}

void FPSCamera::MoveRight(float value)
{
	this->Transform.Translate(Willow::Vec3(value, 0, 0));
}

void FPSCamera::LookUp(float value)
{
	this->Transform.Rotate(Willow::Vec3::Right, value);
}

void FPSCamera::LookRight(float value)
{
	this->Transform.Rotate(Willow::Vec3::Up, value, false);
}