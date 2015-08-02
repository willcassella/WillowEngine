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
	_data.Name = "void";
	_data.DefaultConstructor = [](byte* /*location*/) -> void {};
	_data.CopyConstructor = [](byte* /*location*/, const void* /*copy*/) -> void {};
	_data.MoveConstructor = [](byte* /*location*/, void* /*move*/) -> void {};
	_data.CopyAssignmentOperator = [](void* /*value*/, const void* /*copy*/) -> void {};
	_data.MoveAssignmentOperator = [](void* /*value*/, void* /*move*/) -> void {};
	_data.Destructor = [](void* /*value*/) -> void {};

	_data.ToStringImplementation = [](const void* /*value*/) -> String { return "void"; };
	_data.FromStringImplementation = [](void* /*value*/, const String& string) -> String { return string; };

	_data.Size = 0;
	_data.IsCompound = false;
	_data.IsAbstract = false;
	_data.IsPolymorphic = false;
	_data.IsDefaultConstructible = false;
	_data.IsCopyConstructible = false;
	_data.IsMoveConstructible = false;
	_data.IsCopyAssignable = false;
	_data.IsMoveAssignable = false;
	_data.IsDestructible = false;
}

///////////////////
///   Methods   ///

bool VoidInfo::IsCastableTo(const TypeInfo& type) const
{
	return type == self;
}
