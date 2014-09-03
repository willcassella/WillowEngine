// Transform.cpp

#include "..\..\include\Utility\Math\Transform.h"
using namespace Math;

////////////////////////
///   Constructors   ///

Transform::Transform()
{
	// Set scale to 1 (default for vec3 is 0)
	scale = Vec3(1, 1, 1);
	parent = nullptr;
}

Transform::Transform(const Vec3& _position, const Vec3& _scale, const Quat& _orientation)
{
	position = _position;
	scale = _scale;
	orientation = _orientation;
	parent = nullptr;
}

///////////////////
///   Methods   ///

void Transform::translate(const Math::Vec3& vec, bool isLocal)
{
	Vec3 translateVec = vec;
	if (isLocal)
	{
		translateVec = Mat4::rotate(this->orientation) * translateVec;
	}
	position += translateVec;
}

void Transform::changeScale(const Math::Vec3& vec, bool isLocal)
{
	Vec3 scaleVec = vec;
	if (isLocal)
	{
		scaleVec = Mat4::rotate(this->orientation) * scaleVec;
	}
	scale += scaleVec;
}

void Transform::rotate(const Math::Vec3& axis, float angle, bool isLocal)
{
	orientation.rotateByAxisAngle(axis, angle, isLocal);
}

Mat4 Transform::getModel() const
{
	// Generate the transformation matrices and multiply them together
	if (parent != nullptr)
	{
		return this->parent->getModel() * (Mat4::translate(this->position) * Mat4::rotate(this->orientation) * Mat4::scale(this->scale));
	}
	else
	{
		return Mat4::translate(this->position) * Mat4::rotate(this->orientation) * Mat4::scale(this->scale);
	}
}