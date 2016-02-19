// New.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <cstdlib>
#include "Pointers/Owned.h"

/////////////////////
///   Functions   ///

/** Constructs a new instance of 'T'. */
template <typename T, typename ... ArgT>
Owned<T> New(ArgT&& ... args)
{
	// Construct the object
	auto buffer = std::malloc(sizeof(T));
	new (buffer) T(std::forward<ArgT>(args)...);
	
	// Construct the owner
	Owned<T> owner;
	owner._value = static_cast<T*>(buffer);

	return owner;
}
