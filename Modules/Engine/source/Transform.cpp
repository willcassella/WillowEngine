// Transform.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Engine/Transform.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::Transform)
.Field("location", &Transform::location, "The location of this Transform.")
.Field("rotation", &Transform::rotation, "The rotation of this Transform.")
.Field("scale", &Transform::scale, "The scale of this Transform.")
.Property("matrix", &Transform::get_matrix, nullptr, "Matrix representation of this Transform.");

namespace willow
{
	///////////////////
	///   Methods   ///

	Mat4 Transform::get_matrix() const
	{
		return Mat4::Translate(this->location) * Mat4::Scale(this->scale) * Mat4::Rotate(this->rotation);
	}
}
