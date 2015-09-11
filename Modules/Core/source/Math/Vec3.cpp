// Vec3.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Math/Vec3.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/PrimitiveInfo.h"

///////////////////////
///   Information   ///

BUILD_REFLECTION(Vec3)
.Field("X", &Vec3::X, "")
.Field("Y", &Vec3::Y, "")
.Field("Z", &Vec3::Z, "")
.IsStable();

////////////////////////////
///   Static Instances   ///

const Vec3 Vec3::Zero = Vec3(0, 0, 0);
const Vec3 Vec3::Up = Vec3(0, 1, 0);
const Vec3 Vec3::Forward = Vec3(0, 0, -1);
const Vec3 Vec3::Right = Vec3(1, 0, 0);
