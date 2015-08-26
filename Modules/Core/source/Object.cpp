// Object.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

const ClassInfo Object::StaticTypeInfo = TypeInfoBuilder<Object>();

////////////////////////
///   Constructors   ///

Object::~Object()
{
	for (auto& ref : _references)
	{
		*reinterpret_cast<void**>(ref) = nullptr;
	}
}

///////////////////
///   Methods   ///

String Object::ToString() const
{
	return Implementation::Default::ToString(self);
}

String Object::FromString(const String& string)
{
	return Implementation::Default::FromString(self, string);
}

void Object::ToArchive(ArchNode& node) const
{
	Implementation::Default::ToArchive(self, node);
}
