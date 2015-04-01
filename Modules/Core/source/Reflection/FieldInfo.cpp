// FieldInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/Variant.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(FieldInfo);

///////////////////
///   Methods   ///

Variant FieldInfo::GetValue(Variant owner) const
{
	return Variant(); // @TODO: Implement this
}

void FieldInfo::SetValue(Variant owner, Variant value) const
{
	// @TODO: Implement this
}