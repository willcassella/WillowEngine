// Object.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Forwards/Core.h"
#include "Containers/Array.h"
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
	IMPLEMENTS();

	/** Type information for 'Object' */
	static const ClassInfo StaticTypeInfo;

	/** Ptr needs to be able to add and remove itself from the "_references" Array. */
	template <class ObjectT>
	friend struct Ptr;

	////////////////////////
	///   Constructors   ///
public:

	Object() = default;
	Object(const Object& copy) = delete;
	Object(Object&& move) = delete;
	virtual ~Object();

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

	////////////////
	///   Data   ///
private:

	mutable Array<void*> _references;
};
