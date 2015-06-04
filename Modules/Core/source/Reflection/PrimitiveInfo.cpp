// PrimitiveInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/PrimitiveInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(PrimitiveInfo);

///////////////////
///   Methods   ///

bool PrimitiveInfo::IsCastableTo(const TypeInfo& type) const
{
	return type == This; // Primitives are not castable to anything other than themselves
}