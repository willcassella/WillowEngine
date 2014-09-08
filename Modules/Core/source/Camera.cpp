// Camera.cpp

#include "..\include\Core\Camera.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

Camera::Camera(const String& _name, float _vFOV, float _ratio, float _zMin, float _zMax)
	: Base(_name)
{
	this->vFOV = _vFOV;
	this->ratio = _ratio;
	this->zMin = _zMin;
	this->zMax = _zMax;

	this->perspective = Math::Mat4::perspectiveVFOV(vFOV, ratio, zMin, zMax);
}

///////////////////
///   Methods   ///

void Camera::tick(float timeInterval)
{
	this->transform.translate(Math::Vec3(timeInterval), false);
}

Math::Mat4 Camera::getPerspective() const
{
	return perspective;
}