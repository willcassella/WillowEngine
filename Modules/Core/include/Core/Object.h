// Object.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"
#include "Forwards/Core.h"
#include "Reflection/Reflection.h"

/////////////////
///   Types   ///

/** Base of every polymorphic type in the engine */
class CORE_API Object
{
	///////////////////////
	///   Information   ///
public:

	/** 'Object' does not implement any interfaces. */
	IMPLEMENTS()

	/** Type information for 'Object' */
	static const ClassInfo StaticTypeInfo;

	////////////////////////
	///   Constructors   ///
public:

	Object() = default;
	Object(const Object& copy) = delete;
	Object(Object&& move) = delete;
	virtual ~Object() = default;

	///////////////////
	///   Methods   ///
public:

	/** Returns the type information for this Object. */
	virtual const ClassInfo& GetType() const = 0;

	/** Formats the state of this Object as a String. */
	virtual String ToString() const;

	/////////////////////
	///   Operators   ///
public:

	Object& operator=(const Object& copy) = delete;
	Object& operator=(Object&& move) = delete;
};
