// InterfaceInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/InterfaceInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(InterfaceInfo);

///////////////////
///   Methods   ///

bool InterfaceInfo::IsCastableTo(const TypeInfo& type) const
{
	return type == self || type == TypeOf<Object>();
}