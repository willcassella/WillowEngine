// PropertyInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/PrimitiveInfo.h"
#include "../../include/Core/Reflection/PointerInfo.h"
#include "../../include/Core/Reflection/EnumInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(PropertyInfo)
.Property("Name", &PropertyInfo::_name, nullptr, "The name of this property.")
.Property("Description", &PropertyInfo::_description, nullptr, "A description of this property.")
.Property("Category", &PropertyInfo::_category, nullptr, "The category this property belongs to.")
.Property("Flags", &PropertyInfo::_flags, nullptr, "The flags on this property.")
.Property("Owner Type", &PropertyInfo::_ownerType, nullptr, "The type that owns this property.")
.Property("Property Type", &PropertyInfo::_propertyType, nullptr, "What type this property is.");

BUILD_ENUM_REFLECTION(PropertyFlags)
.IsBitFlag()
.Value("None", PF_None, "This property has no flags.");

////////////////////////
///   Constructors   ///

PropertyInfo::PropertyInfo(CString name, CString description, CString category, PropertyFlags flags)
	: _name(name), _description(description), _category(category), _flags(flags)
{
	// All done
}

Property::Property(const PropertyInfo& info, void* owner)
	: _info(&info), _owner(owner)
{
	// All done
}

ImmutableProperty::ImmutableProperty(const Property& prop)
	: _info(prop._info), _owner(prop._owner)
{
	// All done
}

ImmutableProperty::ImmutableProperty(const PropertyInfo& info, const void* owner)
	: _info(&info), _owner(owner)
{
	// All done
}

///////////////////
///   Methods   ///

Property PropertyInfo::Get(Variant owner) const
{
	assert(owner.GetType().IsCastableTo(*_ownerType));
	return Property(self, owner.GetValue());
}

ImmutableProperty PropertyInfo::Get(ImmutableVariant owner) const
{
	assert(owner.GetType().IsCastableTo(*_ownerType));
	return ImmutableProperty(self, owner.GetValue());
}

String Property::ToString() const
{
	return _info->_toString(_owner);
}

String Property::FromString(const String& string)
{
	// Read only properties may not have mutable operation performed on them.
	assert(_info->IsReadOnly());
	return _info->_fromString(_owner, string);
}

void Property::ToArchive(ArchiveNode& node) const
{
	_info->_toArchive(_owner, node);
}

void Property::FromArchive(const ArchiveNode& node)
{
	// Read only properties may not have mutable operation performed on them.
	assert(_info->IsReadOnly());
	_info->_fromArchive(_owner, node);
}

String ImmutableProperty::ToString() const
{
	return _info->_toString(_owner);
}

void ImmutableProperty::ToArchive(ArchiveNode& node) const
{
	_info->_toArchive(_owner, node);
}
