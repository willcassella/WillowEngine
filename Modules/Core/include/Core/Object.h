// Object.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Reflection/Reflection.h"
#include "Memory/ReferenceCounter.h"
#include "Utility/UnMoveable.h"

/** Base of any polymorphic type that has to act within a larger system.
* May be referenced with 'Weak<T>' and 'Borrowed<T>' smart pointers. */
class CORE_API Object : public willow::UnMoveable
{
	///////////////////////
	///   Inner Types   ///
protected:

	/** Flags for constructing Objects. */
	enum ObjectConstructionFlags
	{
		/** This object is constructed without a reference count block. */
		NoReferenceCount
	};

	///////////////////////
	///   Information   ///
public:

	REFLECTION_DECL(ClassInfo)
	IMPLEMENTS()

	////////////////////////
	///   Constructors   ///
public:

	/** Constructs an Object with a reference counter. */
	Object();
	
	/** Constructs an Object without a reference counter. */
	explicit Object(ObjectConstructionFlags flags);
	
	/** Marks Object as being destroyed (if it's refcounted). */
	virtual ~Object();

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this Object is reference counted. */
	FORCEINLINE bool IsReferenceCounted() const
	{
		return _referenceCounter != nullptr;
	}

	/** Returns a pointer to the reference counter for this Object.
	* NOTE: Returns 'null' if this Object is not reference counted. */
	FORCEINLINE ReferenceCounter* GetReferenceCounter() const
	{
		return _referenceCounter;
	}

	/** Returns the type information for this Object. */
	virtual const ClassInfo& GetType() const = 0;

	/** Formats the state of this Object as a String. */
	virtual String ToString() const;

	////////////////
	///   Data   ///
private:

	ReferenceCounter* _referenceCounter;
};
