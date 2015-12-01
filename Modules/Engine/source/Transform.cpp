// Transform.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Engine/Transform.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Transform)
.Field("Location", &Transform::Location, "The location of this Transform, in 3D coordinates.")
.Field("Orientation", &Transform::Orientation, "The orientation of this Transform.")
.Field("Scale3D", &Transform::Scale, "The scale of this Transform.")
.Field("Mobility", &Transform::_mobility, "The mobility state of this Transform.", FF_EditorOnly);

BUILD_ENUM_REFLECTION(Transform::Mobility)
.Value("Static", Transform::Mobility::Static, "This Transform may not move independtly of its parent.")
.Value("Dynamic", Transform::Mobility::Dynamic, "This Transform may move independtly of its parent.");

///////////////////
///   Methods   ///

String Transform::ToString() const
{
	return Format("{@, @, @}", Location, Orientation, Scale);
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
	Scale *= scaleVec;
}

void Transform::Rotate(const Vec3& axis, float angle, bool isLocal)
{
	Orientation.RotateByAxisAngle(axis, angle, isLocal);
}

Mat4 Transform::GetMatrix() const
{
	return Mat4::Translate(Location) * Mat4::Scale(Scale) * Mat4::Rotate(Orientation);
}
