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
	return Operations::Default::ToString(*this);
}
