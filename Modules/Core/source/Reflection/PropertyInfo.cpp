// PropertyInfo.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

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
.Value("None", PF_None, "This property has no flags.")
.Value("EditorOnly", PF_EditorOnly, "This property should only be exposed to the editor.");

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

Property PropertyInfo::GetFromOwner(Variant owner) const
{
	assert(owner.GetType().is_castable_to(*_ownerType));
	return Property(*this, owner.GetValue());
}

ImmutableProperty PropertyInfo::GetFromOwner(ImmutableVariant owner) const
{
	assert(owner.GetType().is_castable_to(*_ownerType));
	return ImmutableProperty(*this, owner.GetValue());
}

bool Property::HasToStringImplementation() const
{
	return _info->_toString != nullptr;
}

String Property::ToString() const
{
	assert(this->HasToStringImplementation());
	return _info->_toString(_owner);
}

bool Property::HasFromStringImplementation() const
{
	return _info->_fromString != nullptr;
}

String Property::FromString(const String& string)
{
	assert(this->HasFromStringImplementation());
	return _info->_fromString(_owner, string);
}

bool Property::HasToArchiveImplementation() const
{
	return _info->_toArchive != nullptr;
}

void Property::ToArchive(ArchiveWriter& writer) const
{
	assert(this->HasToArchiveImplementation());
	_info->_toArchive(_owner, writer);
}

bool Property::HasFromArchiveImplementation() const
{
	return _info->_fromArchive != nullptr;
}

void Property::FromArchive(const ArchiveReader& reader)
{
	assert(this->HasFromArchiveImplementation());
	_info->_fromArchive(_owner, reader);
}

bool ImmutableProperty::HasToStringImplementation() const
{
	return _info->_toString != nullptr;
}

String ImmutableProperty::ToString() const
{
	assert(this->HasToStringImplementation());
	return _info->_toString(_owner);
}

bool ImmutableProperty::HasToArchiveImplementation() const
{
	return _info->_toArchive != nullptr;
}

void ImmutableProperty::ToArchive(ArchiveWriter& writer) const
{
	assert(this->HasToArchiveImplementation());
	_info->_toArchive(_owner, writer);
}
