// EnumInfo.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/EnumInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(EnumInfo);

///////////////////
///   Methods   ///

bool EnumInfo::IsCastableTo(const TypeInfo& type) const
{
	return type == *this || type == *_data.underlyingType;
}
