// VoidInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/VoidInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(VoidInfo);

////////////////////////
///   Constructors   ///

VoidInfo::VoidInfo(const TypeInfoBuilder<void, VoidInfo>& builder)
	: Base(builder)
{
	// All done
}

TypeInfoBuilder<void, TypeInfo>::TypeInfoBuilder()
{
	_data.rawName = "void";

	_data.size = 0;
	_data.isCompound = false;
	_data.isAbstract = false;
	_data.isPolymorphic = false;
	_data.isTrivial = false;
}

///////////////////
///   Methods   ///

bool VoidInfo::IsCastableTo(const TypeInfo& type) const
{
	return type == self;
}

bool VoidInfo::IsStable() const
{
	return true;
}
