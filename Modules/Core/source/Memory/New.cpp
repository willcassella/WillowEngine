// New.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Memory/New.h"

/////////////////////
///   Functions   ///

template <typename ConstructorT>
Owned<void> AllocateDynamicNew(const TypeInfo& type, ConstructorT&& constructor)
{
	// Allocate memory and construct object
	auto buffer = static_cast<byte*>(std::malloc(type.get_size()));
	constructor(buffer);

	// Create deleter for object
	auto deleter = [](void* value, const TypeInfo* t)
	{
		t->get_destructor()(value);
		std::free(value);
	};

	return Owned<void>::Create(buffer, &type, deleter);
}

Owned<void> DynamicNew(const TypeInfo& type)
{
	if (!type.is_default_constructible() || !type.is_destructible())
	{
		return nullptr;
	}

	// Construct object
	return AllocateDynamicNew(type, type.get_default_constructor());
}

Owned<void> DynamicNew(const TypeInfo& type, DynamicInitializer)
{
	if (!type.is_dynamically_constructible())
	{
		return nullptr;
	}

	// Construct object
	return AllocateDynamicNew(type, type.get_dynamic_constructor());
}

Owned<void> DynamicCopy(ImmutableVariant value)
{
	if (!value.GetType().is_copy_constructible())
	{
		return nullptr;
	}

	// Create constructor
	auto constructor = [&](byte* location)
	{
		value.GetType().get_copy_constructor()(location, value.GetValue());
	};

	// Construct object
	return AllocateDynamicNew(value.GetType(), constructor);
}

Owned<void> DynamicMove(Variant value)
{
	if (!value.GetType().is_move_constructible())
	{
		return nullptr;
	}

	// Create constructor
	auto constructor = [&](byte* location)
	{
		value.GetType().get_move_constructor()(location, value.GetValue());
	};

	// Construct object
	return AllocateDynamicNew(value.GetType(), constructor);
}
