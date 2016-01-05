// UniquePtr.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Memory/UniquePtr.h"
#include "../../include/Core/Reflection/VoidInfo.h"
#include "../../include/Core/Reflection/Variant.h"
#include "../../include/Core/Reflection/StructInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(UniquePtr<void>);

/////////////////////
///   Operators   ///

Variant UniquePtr<void>::operator*()
{
	return Variant(_controller->GetData(), _controller->GetAllocatedType());
}

ImmutableVariant UniquePtr<void>::operator*() const
{
	return ImmutableVariant(_controller->GetData(), _controller->GetAllocatedType());
}
