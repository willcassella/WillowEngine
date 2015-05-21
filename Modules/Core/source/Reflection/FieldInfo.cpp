// FieldInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/Variant.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(FieldInfo);

///////////////////
///   Methods   ///

Variant FieldInfo::GetValue(const Variant& owner) const
{
	if (owner.GetType().IsCastableTo(*_ownerType)) // Make sure the given owner is of a type that owns this field
	{
		if (owner.IsImmutable()) // We must return an immutable Variant
		{
			const void* field = _getter(owner._value);
			return Variant(field, *_fieldType);
		}
		else
		{
			void* field = _getter(owner._value);
			return Variant(field, *_fieldType, false);
		}
	}
	else
	{
		return Variant(); // void Variant
	}
}

Variant FieldInfo::GetValue(Variant&& owner) const
{
	return Variant(); // @TODO: Implement this
}

void FieldInfo::SetValue(const Variant& owner, const Variant& value) const
{
	// @TODO: Implement this
}