// InterfaceInfo.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/InterfaceInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(InterfaceInfo);

///////////////////
///   Methods   ///

bool InterfaceInfo::IsCastableTo(const TypeInfo& type) const
{
	return type == *this || type == TypeOf<Object>();
}