// CompoundInfo.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/CompoundInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/StructInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(CompoundInfo)
.Property("Properties", &CompoundInfo::GetProperties, nullptr, "The collection of properties of this type.")
.Property("Data", &CompoundInfo::GetData, nullptr, "The collection of data on this type.");

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

Array<DataInfo> CompoundInfo::GetData() const
{
	return _data.DataMembers;
}

const DataInfo* CompoundInfo::FindData(const String& name) const
{
	auto index = _data.DataTable.Find(name);
	if (index)
	{
		return &_data.DataMembers[*index];
	}
	else
	{
		return nullptr;
	}
}
