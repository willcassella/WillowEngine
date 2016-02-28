// Owned.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Core/IO/Console.h"
#include "../../../include/Core/Reflection/StructInfo.h"
#include "../../../include/Core/Memory/Pointers/Owned.h"
#include "../../../include/Core/Reflection/VoidInfo.h"
#include "../../../include/Core/Reflection/Variant.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Owned<void>);

/////////////////////
///   Operators   ///

Variant Owned<void>::operator*()
{
	assert(*this != nullptr);
	return Variant(_value, *_type);
}

ImmutableVariant Owned<void>::operator*() const
{
	assert(*this != nullptr);
	return ImmutableVariant(_value, *_type);
}
