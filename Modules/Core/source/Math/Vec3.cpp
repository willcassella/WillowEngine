// Vec3.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Math/Vec3.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/PrimitiveInfo.h"

///////////////////////
///   Information   ///

STRUCT_REFLECTION(Vec3)
.AddProperty("X", "", &Vec3::X)
.AddProperty("Y", "", &Vec3::Y)
.AddProperty("Z", "", &Vec3::Z);

////////////////////////////
///   Static Instances   ///

const Vec3 Vec3::Zero = Vec3(0, 0, 0);
const Vec3 Vec3::Up = Vec3(0, 1, 0);
const Vec3 Vec3::Forward = Vec3(0, 0, -1);
const Vec3 Vec3::Right = Vec3(1, 0, 0);