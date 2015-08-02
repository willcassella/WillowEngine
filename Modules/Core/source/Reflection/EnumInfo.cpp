// EnumInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/EnumInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(EnumInfo);

///////////////////
///   Methods   ///

bool EnumInfo::IsCastableTo(const TypeInfo& type) const
{
	return type == self || type == *_underlyingType;
}
