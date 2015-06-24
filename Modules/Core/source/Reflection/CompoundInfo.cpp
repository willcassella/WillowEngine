// CompoundInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/CompoundInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/StructInfo.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(CompoundInfo)
.AddProperty("Properties", "The collection of properties of this type.", &CompoundInfo::GetProperties, nullptr);

///////////////////
///   Methods   ///

Array<PropertyInfo> CompoundInfo::GetProperties() const
{
	return _properties;
}

const PropertyInfo* CompoundInfo::FindProperty(const String& name) const
{
	auto index = _propertyTable.Find(name);
	if (index)
	{
		return &_properties[*index];
	}
	else
	{
		return nullptr;
	}
}