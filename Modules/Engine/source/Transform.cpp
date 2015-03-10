// Transform.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Engine/Transform.h"

//////////////////////
///   Reflection   ///

STRUCT_REFLECTION(Transform)
.AddField("Location", &Transform::Location)
.AddField("Orientation", &Transform::Orientation)
.AddField("Scale3D", &Transform::Scale3D)
.AddField("Parent", &Transform::Parent);

///////////////////
///   Methods   ///

String Transform::ToString() const
{
	return TypeOf<String>().GetName();
}

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