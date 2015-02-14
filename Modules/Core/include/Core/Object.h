// Object.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "String.h"
#include "Reflection/Reflection.h"

/** Base class of every class in the engine (see coding guide for "class").
* It has first-class support for reflection, which makes it very handy for game programming */
class CORE_API Object
{
	////////////////////////
	///   Constructors   ///
public:

	virtual ~Object() = default;

	///////////////////
	///   Methods   ///
public:

	/** Returns a String representation of this Object */
	virtual String ToString() const;

	/** Returns the type information for this object */
	virtual const ClassInfo& GetType() const = 0;

	/** Returns whether this object is an instance of the given class */
	bool IsA(const ClassInfo& type) const;

	/** Returns whether this object implements the given interface */
	bool Implements(const InterfaceInfo& interf) const;

	/** Returns whether this Object is an instance of the given class */
	template <class AnyClass>
	FORCEINLINE bool IsA() const
	{
		// If your code fails here, 'AnyClass' is not a reflectable class
		return IsA(AnyClass::StaticTypeInfo);
	}

	/** Returns whether this Object implements the given interface */
	template <class AnyInterface>
	FORCEINLINE bool Implements() const
	{
		// If your code fails here, 'AnyInterface' is not a reflectable interface
		return Implements(AnyInterface::StaticTypeInfo());
	}

	/** Type information for 'Object' */
	static const ClassInfo StaticTypeInfo;
};