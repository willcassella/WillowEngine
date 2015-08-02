// PrimitiveInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/PrimitiveInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(PrimitiveInfo);

///////////////////
///   Methods   ///

bool PrimitiveInfo::IsCastableTo(const TypeInfo& type) const
{
	return type == self; // Primitives are not castable to anything other than themselves
}