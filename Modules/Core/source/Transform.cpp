// Transform.cpp

#include "..\include\Core\Transform.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

Transform::Transform(Mobility::Mobility mobility, const Vec3& location, const Quat& orientation, const Vec3& scale3D)
{
	this->Location = location;
	this->Scale3D = scale3D;
	this->Orientation = orientation;
	this->Parent = nullptr;
	this->_mobility = mobility;
}

///////////////////
///   Methods   ///

void Transform::Translate(const Vec3& vec, bool isLocal)
{
	Vec3 translateVec = vec;
	if (isLocal)
	{
		translateVec = Mat4::Rotate(Orientation) * translateVec;
	}
	Location += translateVec;
}

void Transform::Scale(const Vec3& vec, bool isLocal)
{
	Vec3 scaleVec = vec;
	if (isLocal)
	{
		scaleVec = Mat4::Rotate(Orientation) * scaleVec;
	}
	Scale3D += scaleVec;
}

void Transform::Rotate(const Vec3& axis, float angle, bool isLocal)
{
	Orientation.RotateByAxisAngle(axis, angle, isLocal);
}

Mat4 Transform::GetTransfomationMatrix() const
{
	// Generate the transformation matrices and multiply them together
	if (Parent != nullptr)
	{
		return Parent->GetTransfomationMatrix() * (Mat4::Translate(Location) * Mat4::Rotate(Orientation) * Mat4::Scale(Scale3D));
	}
	else
	{
		return Mat4::Translate(Location) * Mat4::Rotate(Orientation) * Mat4::Scale(Scale3D);
	}
}