// Object.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Reflection/Reflection.h"

/** Base of every polymorphic type in the engine */
class CORE_API Object
{
	///////////////////////
	///   Information   ///
public:

	/** Type information for 'Object' */
	static const ClassInfo StaticTypeInfo;

	////////////////////////
	///   Constructors   ///
public:

	virtual ~Object() = default;

	///////////////////
	///   Methods   ///
public:

	/** Returns the type information for this Object */
	virtual const ClassInfo& GetType() const = 0;
};