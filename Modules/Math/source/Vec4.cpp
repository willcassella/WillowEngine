// Vec4.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Math/Vec4.h"

//////////////////////
///   Reflection   ///

STRUCT_REFLECTION(Vec4)
.AddField("X", &Vec4::X)
.AddField("Y", &Vec4::Y)
.AddField("Z", &Vec4::Z)
.AddField("W", &Vec4::W);

////////////////////////////
///   Static Instances   ///

const Vec4 Vec4::Zero = Vec4(0, 0, 0, 0);