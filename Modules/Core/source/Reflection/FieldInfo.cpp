// FieldInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(FieldInfo);

///////////////////
///   Methods   ///

Variant FieldInfo::GetValue(const Variant& owner) const
{
	if (owner.GetType().IsCastableTo(_ownerType)) // Make sure the given owner is of a type that owns this field
	{
		void* field = _getter(owner.GetValue());
		return Variant(field, _fieldType);
	}
	else
	{
		return Variant(); // void Variant
	}
}

ImmutableVariant FieldInfo::GetValue(const ImmutableVariant& owner) const
{
	if (owner.GetType().IsCastableTo(_ownerType)) // Make sure the given owner is of a type that owns this field
	{
		const void* field = _getter(const_cast<void*>(owner.GetValue()));
		return ImmutableVariant(field, _fieldType);
	}
	else
	{
		return Variant(); // void Variant
	}
}

void FieldInfo::SetValue(const Variant& owner, const ImmutableVariant& value) const
{
	if (_fieldType->IsCopyAssignable()) // Make sure this field is settable to begin with
	{
		if (owner.GetType().IsCastableTo(_ownerType)) // Make sure the given owner is of a type that owns this field
		{
			if (value.GetType().IsCastableTo(_fieldType)) // Make sure the given value is of a type that this field can be assigned to
			{
				_setter(owner.GetValue(), value.GetValue());
			}
		}
	}
}