// Vec4.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Math/Vec4.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/PrimitiveInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Vec4)
.AddProperty("X", "", &Vec4::X)
.AddProperty("Y", "", &Vec4::Y)
.AddProperty("Z", "", &Vec4::Z)
.AddProperty("W", "", &Vec4::W)
.IsStable();

////////////////////////////
///   Static Instances   ///

const Vec4 Vec4::Zero = Vec4(0, 0, 0, 0);
