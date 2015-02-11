// Interface.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "String.h"
#include "Reflection/Reflection.h"

/** Base of every interface in the engine */
class CORE_API Interface
{
	////////////////////////
	///   Constructors   ///
public:

	virtual ~Interface() = 0;

	///////////////////
	///   Methods   ///
public:

	/** Returns a String representation of this Object */
	String ToString() const;

	/** Returns the underlying type of this Object */
	const ClassInfo& GetType() const;
};

/** 'Interface' is abstract */
inline Interface::~Interface() {};