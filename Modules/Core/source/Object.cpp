// Object.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

const ClassInfo Object::StaticTypeInfo = TypeInfoBuilder<Object>();

///////////////////
///   Methods   ///

String Object::ToString() const
{
	return Implementation::Default::ToString(self);
}
