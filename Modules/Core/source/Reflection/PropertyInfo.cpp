// PropertyInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/PrimitiveInfo.h"
#include "../../include/Core/Reflection/PointerInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(PropertyInfo)
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

PropertyInfo::PropertyInfo(CString name, CString description, PropertyFlags flags)
	: _name(name), _description(description), _flags(flags)
{
	// All done
}

///////////////////
///   Methods   ///

Variant PropertyInfo::GetMutableValue(Variant owner) const
{
	assert(owner.GetType().IsCastableTo(*_ownerType));
	assert(HasMutableGetter());

	return _mutableGetter(owner.GetValue());
}

void PropertyInfo::SetValue(Variant owner, ImmutableVariant value) const
{
	assert(owner.GetType().IsCastableTo(*_ownerType));
	assert(value.GetType().IsCastableTo(*_propertyType));
	assert(HasSetter());

	return _setter(owner.GetValue(), value.GetValue());
}
