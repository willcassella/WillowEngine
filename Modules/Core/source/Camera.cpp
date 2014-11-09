// Camera.cpp

#include "..\include\Core\Camera.h"
using namespace Willow;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(Willow::Camera)
HAS_FACTORY
FIELD(VFOV)
FIELD(Ratio)
FIELD(ZMin)
FIELD(ZMax)
END_REFLECTION_INFO

////////////////////////
///   Constructors   ///

Camera::Camera(const String& name, float vFOV, float ratio, float zMin, float zMax)
	: Super(name)
{
	this->VFOV = vFOV;
	this->Ratio = ratio;
	this->ZMin = zMin;
	this->ZMax = zMax;
}

///////////////////
///   Methods   ///

Mat4 Camera::GetPerspective() const
{
	return Mat4::PerspectiveVFOV(VFOV, Ratio, ZMin, ZMax);
}