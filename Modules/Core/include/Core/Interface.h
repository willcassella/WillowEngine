// Interface.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

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

	/** Returns the underlying type of the Object implementing this interface */
	const ClassInfo& GetType() const;
};

/** 'Interface' is abstract */
inline Interface::~Interface() {};