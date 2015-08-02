// CompoundInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/CompoundInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/StructInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(CompoundInfo)
.AddProperty("Properties", "The collection of properties of this type.", &CompoundInfo::GetProperties, nullptr);

///////////////////
///   Methods   ///

Array<PropertyInfo> CompoundInfo::GetProperties() const
{
	return _data.Properties;
}

const PropertyInfo* CompoundInfo::FindProperty(const String& name) const
{
	auto index = _data.PropertyTable.Find(name);
	if (index)
	{
		return &_data.Properties[*index];
	}
	else
	{
		return nullptr;
	}
}