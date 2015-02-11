// Exception.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "String.h"

/** Base of every exception in the engine */
class CORE_API Exception
{
	////////////////////////
	///   Constructors   ///
public:

	virtual ~Exception() = default;

	///////////////////
	///   Methods   ///
public:

	/** Returns the error message */
	virtual String GetError() const = 0;
};