// Interface.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Core/Object.h"
#include "../include/Core/Interface.h"

///////////////////
///   Methods   ///

const ClassInfo& Interface::GetType() const
{
	return reinterpret_cast<const Object*>(this)->GetType();
}