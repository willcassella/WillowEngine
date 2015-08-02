// StructInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(StructInfo);

///////////////////
///   Methods   ///

bool StructInfo::IsCastableTo(const TypeInfo& type) const
{
	// Structs are never castable to anything other than themselves
	return type == self;
}
