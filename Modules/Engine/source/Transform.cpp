// Transform.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Engine/Transform.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Transform)
.Field("Location", &Transform::Location, "The location of this GameObject, in 3D coordinates.")
.Field("Orientation", &Transform::Orientation, "The orientation of this GameObject.")
.Field("Scale3D", &Transform::Scale, "The scale of this GameObject");

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

void Transform::Scale3D(const Vec3& vec, bool isLocal)
{
	Vec3 scaleVec = vec;
	if (isLocal)
	{
		scaleVec = Mat4::Rotate(Orientation) * scaleVec;
	}
	Scale += scaleVec;
}

void Transform::Rotate(const Vec3& axis, float angle, bool isLocal)
{
	Orientation.RotateByAxisAngle(axis, angle, isLocal);
}

Mat4 Transform::GetMatrix() const
{
	return Mat4::Translate(Location) * Mat4::Scale(Scale) * Mat4::Rotate(Orientation);
}
