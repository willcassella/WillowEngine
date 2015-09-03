// Vec2.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Math/Vec2.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/PrimitiveInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Vec2)
.AddProperty("X", "", &Vec2::X)
.AddProperty("Y", "", &Vec2::Y)
.IsStable();

////////////////////////////
///   Static Instances   ///

const Vec2 Vec2::Zero = Vec2(0, 0);
const Vec2 Vec2::Up = Vec2(0, 1);
const Vec2 Vec2::Right = Vec2(1, 0);
