// Object.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

const ClassInfo Object::StaticTypeInfo = TypeInfoBuilder<Object>();

////////////////////////
///   Constructors   ///

Object::~Object()
{
	for (auto ref : _references)
	{
		memset(ref, 0, sizeof(Object*));
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

void Object::ToArchive(ArchiveNode& node) const
{
	Implementation::Default::ToArchive(self, node);
}

void Object::FromArchive(const ArchiveNode& node)
{
	Implementation::Default::FromArchive(self, node);
}
