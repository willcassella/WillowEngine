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
}

///////////////////
///   Methods   ///

Mat4 Camera::GetPerspective() const
{
	return Perspective;
}