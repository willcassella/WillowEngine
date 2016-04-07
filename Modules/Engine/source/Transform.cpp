// Transform.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Engine/Transform.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::Transform)
.Field("Location", &Transform::Location, "The location of this Transform.")
.Field("Rotation", &Transform::Rotation, "The rotation of this Transform.")
.Field("Scale", &Transform::Scale, "The scale of this Transform.")
.Property("Matrix", &Transform::GetMatrix, nullptr, "Matrix representation of this Transform.");

namespace Willow
{
	///////////////////
	///   Methods   ///

	Mat4 Transform::GetMatrix() const
	{
		return Mat4::Translate(this->Location) * Mat4::Scale(this->Scale) * Mat4::Rotate(this->Rotation);
	}
}
