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
	///   Inner Types   ///
public:

	enum class ReferenceClearState : byte
	{
		/** The application must scan for and nullify all references to this object once it has been destroyed. */
		Required,

		/** The application has already scanned for and nullified all references to this object - new references should not be created. */
		Complete,

		/** The application will not scan for and nullify references to this object upon destruction, as that behavior is not necessary or managed elsewhere. */
		NotRequired
	};

	///////////////////////
	///   Information   ///
public:

	REFLECTION_DECL(ClassInfo)
	IMPLEMENTS()

	/** Ptr needs to be able to add and remove itself from the "_references" Array. */
	template <class ObjectT>
	friend struct Ptr;

	////////////////////////
	///   Constructors   ///
public:

	Object();
	Object(const Object& copy) = delete;
	Object(Object&& move) = delete;
	virtual ~Object();

	//////////////////
	///   Fields   ///
public:

	/** Indicates whether references to this object should be cleared upon its destruction (defaults to 'Required').
	* NOTE: 99% of the time this should remain unmodified. This should only be changed if this Object is being managed specially. */
	ReferenceClearState ReferenceClearStatus;

	///////////////////
	///   Methods   ///
public:

	/** Returns the type information for this Object. */
	virtual const ClassInfo& GetType() const = 0;

	/** Formats the state of this Object as a String. */
	virtual String ToString() const;

	/** Sets the state of this Object from the given String. */
	virtual String FromString(const String& string);

	/** Serializes the state of this Object to the given archive node. */
	virtual void ToArchive(ArchiveNode& node) const;

	/** Deserializes the state of this Object from the given archive node. */
	virtual void FromArchive(const ArchiveNode& node);

	/////////////////////
	///   Operators   ///
public:

	Object& operator=(const Object& copy) = delete;
	Object& operator=(Object&& move) = delete;

	////////////////
	///   Data   ///
private:

	// @TODO: Remove this in favor of managed references
	mutable Array<void*> _references;
};
