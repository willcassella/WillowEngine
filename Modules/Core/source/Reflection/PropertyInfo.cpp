// PropertyInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/PrimitiveInfo.h"
#include "../../include/Core/Reflection/PointerInfo.h"
#include "../../include/Core/Reflection/EnumInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(PropertyInfo)
.AddProperty("Name", "The name of this property", &PropertyInfo::_name, nullptr)
.AddProperty("Description", "A description of this property.", &PropertyInfo::_description, nullptr)
.AddProperty("Flags", "The flags on this property.", &PropertyInfo::_flags, nullptr)
.AddProperty("Owner Type", "The type that owns this property.", &PropertyInfo::_ownerType, nullptr)
.AddProperty("Property Type", "What type this property is.", &PropertyInfo::_propertyType, nullptr);

ENUM_REFLECTION(PropertyFlags)
.IsBitFlag()
.AddValue<PF_None>("None")
.AddValue<PF_NoSerialize>("No Serialize")
.AddValue<PF_Set_SerializeOnly>("Set Serialize-Only");

ENUM_REFLECTION(PropertyAccess)
.AddValue<PropertyAccess::Field>("Field")
.AddValue<PropertyAccess::NoSetField>("No-Set Field")
.AddValue<PropertyAccess::Property>("Property")
.AddValue<PropertyAccess::ReadOnlyProperty>("Read-Only Property");

////////////////////////
///   Constructors   ///

PropertyInfo::PropertyInfo(CString name, CString description, PropertyFlags flags)
	: _name(name), _description(description), _flags(flags)
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

String Property::FromString(const String& string) const
{
	// Read only properties may not have mutable operation performed on them.
	assert(_info->GetAccess() != PropertyAccess::ReadOnlyProperty);

	return _info->_fromString(_owner, string);
}

void Property::SetValue(ImmutableVariant value) const
{
	assert(value.GetType().IsCastableTo(_info->GetPropertyType()));
	assert(_info->GetAccess() != PropertyAccess::ReadOnlyProperty && _info->GetAccess() != PropertyAccess::NoSetField);

	_info->_setter(_owner, value.GetValue());
}

Variant Property::GetField() const
{
	assert(_info->GetAccess() == PropertyAccess::Field || _info->GetAccess() == PropertyAccess::NoSetField);

	auto value = const_cast<void*>(_info->_fieldGetter(_owner));
	return Variant(value, _info->GetPropertyType());
}

String ImmutableProperty::ToString() const
{
	return _info->_toString(_owner);
}

ImmutableVariant ImmutableProperty::GetField() const
{
	assert(_info->GetAccess() == PropertyAccess::Field || _info->GetAccess() == PropertyAccess::NoSetField);

	auto value = _info->_fieldGetter(_owner);
	return ImmutableVariant(value, _info->GetPropertyType());
}
