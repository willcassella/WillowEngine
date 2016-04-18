// StructInfo.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/PrimitiveInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(StructInfo)
.Property("Stable", &StructInfo::is_stable, nullptr, "Whether the layout of this struct is stable.");

///////////////////
///   Methods   ///

bool StructInfo::is_castable_to(const TypeInfo& type) const
{
	// Structs are never castable to anything other than themselves
	return type == *this;
}

bool StructInfo::is_stable() const
{
	return _data.isStable;
}
