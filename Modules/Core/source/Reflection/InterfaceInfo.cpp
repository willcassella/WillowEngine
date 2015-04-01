// InterfaceInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/InterfaceInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(InterfaceInfo);

////////////////////////
///   Constructors   ///

InterfaceInfo::InterfaceInfo(InterfaceInfo&& move)
	: Super(std::move(move))
{
	// All done
}

///////////////////
///   Methods   ///

bool InterfaceInfo::IsCastableTo(const TypeInfo& type) const
{
	return type == This || type == TypeOf<Object>();
}