// Interface.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"
#include "Forwards/Reflection.h"

/** Base of every interface in the engine. */
class CORE_API Interface
{
	////////////////////////
	///   Constructors   ///
public:

	Interface() = default;
	Interface(const Interface& copy) = delete;
	Interface(Interface&& move) = delete;
	virtual ~Interface() = default;

	///////////////////
	///   Methods   ///
public:

	/** Returns the underlying type of the Object implementing this interface. */
	virtual const ClassInfo& GetType() const = 0;

	/////////////////////
	///   Operators   ///
public:

	Interface& operator=(const Interface& copy) = delete;
	Interface& operator=(Interface&& move) = delete;
};
