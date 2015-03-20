// Camera.cpp

#include "..\include\Core\Camera.h"
using namespace Willow;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(Willow::Camera)
HAS_FACTORY
FIELD(VFOV)
FIELD(HFOV)
FIELD(ZMin)
FIELD(ZMax)
END_REFLECTION_INFO

///////////////////
///   Methods   ///

Mat4 Camera::GetPerspective() const
{
	return Mat4::Perspective(HFOV, VFOV, ZMin, ZMax);
}