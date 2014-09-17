// Camera.cpp

#include "..\include\Core\Camera.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

Camera::Camera(const String& name, float vFOV, float ratio, float zMin, float zMax)
	: Super(name)
{
	this->VFOV = vFOV;
	this->Ratio = ratio;
	this->ZMin = zMin;
	this->ZMax = zMax;

	this->Perspective = Mat4::PerspectiveVFOV(VFOV, Ratio, ZMin, ZMax);

	this->InputHandler.BindAxis("Forward", this, &Camera::MoveForward);
}

///////////////////
///   Methods   ///

void Camera::Tick(float timeInterval)
{
	// Do nothing (replaced with event handler)
}

Mat4 Camera::GetPerspective() const
{
	return Perspective;
}

///////////////////
///   Actions   ///

void Camera::MoveForward(float value)
{
	this->Transform.Translate(Vec3(value, 0, 0), true);
}