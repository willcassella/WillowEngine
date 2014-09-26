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

	EventManager.BindAction("Forward", this, &Camera::MoveForward);
}

///////////////////
///   Methods   ///

Mat4 Camera::GetPerspective() const
{
	return Perspective;
}

void Camera::MoveForward()
{
	this->Transform.Translate(Vec3(0.001f, 0, 0), true);
}