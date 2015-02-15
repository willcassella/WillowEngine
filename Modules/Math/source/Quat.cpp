// Quat.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Math/Quat.h"

//////////////////////
///   Reflection   ///

STRUCT_REFLECTION(Quat)
.AddField("X", &Quat::X)
.AddField("Y", &Quat::Y)
.AddField("Z", &Quat::Z)
.AddField("W", &Quat::W);