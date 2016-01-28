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
	return Implementation::Default::ToString(*this);
}

String Object::FromString(const String& string)
{
	return Implementation::Default::FromString(*this, string);
}

void Object::ToArchive(ArchiveWriter& writer) const
{
	Implementation::Default::ToArchive(*this, writer);
}

void Object::FromArchive(const ArchiveReader& reader)
{
	Implementation::Default::FromArchive(*this, reader);
}
