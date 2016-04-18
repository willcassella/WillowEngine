// VoidInfo.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

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
	_data.type_info = &typeid(void);
	_data.raw_name = "void";

	_data.size = 0;
	_data.alignment = 0;
	_data.is_compound = false;
	_data.is_abstract = false;
	_data.is_polymorphic = false;
	_data.is_trivial = false;
}

///////////////////
///   Methods   ///

bool VoidInfo::is_castable_to(const TypeInfo& type) const
{
	return type == *this;
}

bool VoidInfo::is_stable() const
{
	return true;
}
