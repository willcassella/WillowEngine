// Quat.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Math/Quat.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/PrimitiveInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Quat)
.Field("X", &Quat::X, "")
.Field("Y", &Quat::Y, "")
.Field("Z", &Quat::Z, "")
.Field("W", &Quat::W, "")
.IsStable();
