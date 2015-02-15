// Vec3.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Math/Vec3.h"

///////////////////////
///   Information   ///

STRUCT_REFLECTION(Vec3)
.AddField("X", &Vec3::X)
.AddField("Y", &Vec3::Y)
.AddField("Z", &Vec3::Z);

////////////////////////////
///   Static Instances   ///

const Vec3 Vec3::Zero = Vec3(0, 0, 0);
const Vec3 Vec3::Up = Vec3(0, 1, 0);
const Vec3 Vec3::Forward = Vec3(0, 0, -1);
const Vec3 Vec3::Right = Vec3(1, 0, 0);