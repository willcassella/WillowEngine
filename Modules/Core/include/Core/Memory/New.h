// New.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Pointers/Owned.h"

/////////////////////
///   Functions   ///

/** Constructs a new instance of the given type, using the reflected default constructor.
* NOTE: If the given type does not have a default constructor, this returns 'null'. */
Owned<void> CORE_API DynamicNew(const TypeInfo& type);

/** Constructs a new instance of the given type, using the reflected dynamic constructor.
* NOTE: If the given type does not have a dynamic constructor, this returns 'null'. */
Owned<void> CORE_API DynamicNew(const TypeInfo& type, DynamicInitializer);

/** Dynamically copies the given ImmutableVariant */
Owned<void> CORE_API DynamicCopy(ImmutableVariant value);

/** Dynamically moves the given Variant. */
Owned<void> CORE_API DynamicMove(Variant value);

/** Constructs a new instance of 'T'. */
template <typename T, typename ... ArgT>
Owned<T> New(ArgT&& ... args)
{
	auto pointer = new T{ std::forward<ArgT>(args)... };
	auto deleter = [](void* value, const TypeInfo*) { delete static_cast<T*>(value); };
	
	return Owned<T>::Create(pointer, deleter);
}
