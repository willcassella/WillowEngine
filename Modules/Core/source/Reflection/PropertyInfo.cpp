// PropertyInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/StructInfo.h"

//////////////////////
///   Reflection   ///

STRUCT_REFLECTION(PropertyInfo)
.AddProperty("Name", "The name of this property", &PropertyInfo::_name, nullptr)
.AddProperty("Description", "A description of this property.", &PropertyInfo::_description, nullptr)
.AddProperty("Owner Type", "The type that owns this property.", &PropertyInfo::GetOwnerType, nullptr)
.AddProperty("Property Type", "What type this property is.", &PropertyInfo::GetPropertyType, nullptr)
.AddProperty("Field", "Whether this property is a field.", &PropertyInfo::_isField, nullptr)
.AddProperty("Mutable Getter", "Whether this property has a mutable getter.", &PropertyInfo::HasMutableGetter, nullptr)
.AddProperty("Immutable Getter", "Whether this property has an immutable getter.", &PropertyInfo::HasGetter, nullptr)
.AddProperty("Setter", "Whether this property has a setter.", &PropertyInfo::HasSetter, nullptr);

////////////////////////
///   Constructors   ///

PropertyInfo::PropertyInfo(const String& name, const String& description)
	: _name(name), _description(description)
{
	
}

///////////////////
///   Methods   ///

void PropertyInfo::SetValue(const Variant& owner, const ImmutableVariant& value) const
{
	if (owner.GetType().IsCastableTo(*_ownerType) && value.GetType().IsCastableTo(_propertyType))
	{
		_setter(owner.GetValue(), value.GetValue());
	}
}