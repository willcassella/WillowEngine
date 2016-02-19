// Object.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

const ClassInfo Object::StaticTypeInfo = TypeInfoBuilder<Object>();

////////////////////////
///   Constructors   ///

Object::Object()
	: _referenceCounter(new ReferenceCounter())
{
	// All done
}

Object::Object(ObjectConstructionFlags flags)
{
	if (flags & NoReferenceCount)
	{
		_referenceCounter = nullptr;
	}
	else
	{
		_referenceCounter = new ReferenceCounter();
	}
}

Object::~Object()
{
	if (this->IsReferenceCounted())
	{
		// Tell the reference counter that we've been destroyed
		_referenceCounter->SetDestroyed();
	}
}

///////////////////
///   Methods   ///

String Object::ToString() const
{
	return Operations::Default::ToString(*this);
}
