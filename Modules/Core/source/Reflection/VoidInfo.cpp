// VoidInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/VoidInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(VoidInfo);

////////////////////////
///   Constructors   ///

VoidInfo::VoidInfo(TypeInfoBuilder<void, VoidInfo>& builder)
	: Base(builder)
{
	// All done
}

TypeInfoBuilder<void, TypeInfo>::TypeInfoBuilder()
{
	_data.name = "void";
	_data.defaultConstructor = [](byte* /*location*/) -> void {};
	_data.copyConstructor = [](byte* /*location*/, const void* /*copy*/) -> void {};
	_data.moveConstructor = [](byte* /*location*/, void* /*move*/) -> void {};
	_data.copyAssignmentOperator = [](void* /*value*/, const void* /*copy*/) -> void {};
	_data.moveAssignmentOperator = [](void* /*value*/, void* /*move*/) -> void {};
	_data.destructor = [](void* /*value*/) -> void {};

	_data.toStringImplementation = [](const void* /*value*/) -> String { return "void"; };
	_data.fromStringImplementation = [](void* /*value*/, const String& string) -> String { return string; };

	_data.size = 0;
	_data.isCompound = false;
	_data.isAbstract = false;
	_data.isPolymorphic = false;
	_data.isDefaultConstructible = false;
	_data.isCopyConstructible = false;
	_data.isMoveConstructible = false;
	_data.isCopyAssignable = false;
	_data.isMoveAssignable = false;
	_data.isDestructible = false;
}

///////////////////
///   Methods   ///

bool VoidInfo::IsCastableTo(const TypeInfo& type) const
{
	return type == self;
}
