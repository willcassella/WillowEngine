// Object.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

const ClassInfo Object::StaticTypeInfo = ClassInfo(sizeof(Object), "Object", nullptr, true);

///////////////////
///   Methods   ///

String Object::ToString() const
{
	return GetType().GetName();
}

bool Object::IsA(const ClassInfo& type) const
{
	return GetType() == type || GetType().ExtendsClass(type);
}

bool Object::Implements(const InterfaceInfo& interf) const
{
	return GetType().ImplementsInterface(interf);
}