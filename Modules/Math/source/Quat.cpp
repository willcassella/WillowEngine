// Quat.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Math/Quat.h"

//////////////////////
///   Reflection   ///

STRUCT_REFLECTION(Quat)
.AddProperty("X", "", &Quat::X)
.AddProperty("Y", "", &Quat::Y)
.AddProperty("Z", "", &Quat::Z)
.AddProperty("W", "", &Quat::W);