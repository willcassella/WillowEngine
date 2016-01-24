// Transform.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Engine/Transform.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Transform)
.Data("Location", &Transform::_location)
.Data("Rotation", &Transform::_rotation)
.Data("Scale", &Transform::_scale)
.Property("Location", &Transform::GetLocation, &Transform::SetLocation, "The location of this Transform.")
.Property("Rotation", &Transform::GetRotation, &Transform::SetRotation, "The rotation of this Transform.")
.Property("Scale", &Transform::GetScale, &Transform::SetScale, "The scale of this Transform.")
.Property("Matrix", &Transform::GetMatrix, nullptr, "Matrix representation of this Transform.");

///////////////////
///   Methods   ///

Mat4 Transform::GetMatrix() const
{
	return Mat4::Translate(_location) * Mat4::Scale(_scale) * Mat4::Rotate(_rotation);
}
