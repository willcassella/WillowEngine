// Vec4.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Math/Vec4.h"

//////////////////////
///   Reflection   ///

STRUCT_REFLECTION(Vec4)
.AddProperty("X", "", &Vec4::X)
.AddProperty("Y", "", &Vec4::Y)
.AddProperty("Z", "", &Vec4::Z)
.AddProperty("W", "", &Vec4::W);

////////////////////////////
///   Static Instances   ///

const Vec4 Vec4::Zero = Vec4(0, 0, 0, 0);