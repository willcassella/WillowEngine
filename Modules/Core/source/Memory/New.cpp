// New.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Memory/New.h"

/////////////////////
///   Functions   ///

template <typename ConstructorT>
Owned<void> AllocateDynamicNew(const TypeInfo& type, ConstructorT&& constructor)
{
	// Allocate memory and construct object
	auto buffer = static_cast<byte*>(std::malloc(type.GetSize()));
	constructor(buffer);

	// Create deleter for object
	auto deleter = [](void* value, const TypeInfo* t)
	{
		t->GetDestructor()(value);
		std::free(value);
	};

	return Owned<void>::Create(buffer, &type, deleter);
}

Owned<void> DynamicNew(const TypeInfo& type)
{
	if (!type.IsDefaultConstructible() || !type.IsDestructible())
	{
		return nullptr;
	}

	// Construct object
	return AllocateDynamicNew(type, type.GetDefaultConstructor());
}

Owned<void> DynamicNew(const TypeInfo& type, DynamicInitializer)
{
	if (!type.HasDynamicConstructor())
	{
		return nullptr;
	}

	// Construct object
	return AllocateDynamicNew(type, type.GetDynamicConstructor());
}

Owned<void> DynamicCopy(ImmutableVariant value)
{
	if (!value.GetType().IsCopyConstructible())
	{
		return nullptr;
	}

	// Create constructor
	auto constructor = [&](byte* location)
	{
		value.GetType().GetCopyConstructor()(location, value.GetValue());
	};

	// Construct object
	return AllocateDynamicNew(value.GetType(), constructor);
}

Owned<void> DynamicMove(Variant value)
{
	if (!value.GetType().IsMoveConstructible())
	{
		return nullptr;
	}

	// Create constructor
	auto constructor = [&](byte* location)
	{
		value.GetType().GetMoveConstructor()(location, value.GetValue());
	};

	// Construct object
	return AllocateDynamicNew(value.GetType(), constructor);
}
