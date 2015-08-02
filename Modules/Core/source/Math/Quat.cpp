// Quat.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Math/Quat.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/PrimitiveInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Quat)
.AddProperty("X", "", &Quat::X)
.AddProperty("Y", "", &Quat::Y)
.AddProperty("Z", "", &Quat::Z)
.AddProperty("W", "", &Quat::W);