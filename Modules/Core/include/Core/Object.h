// Object.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Forwards/Core.h"
#include "Containers/Array.h"
#include "Reflection/Reflection.h"
#include "Memory/MemoryBlock.h"

/////////////////
///   Types   ///

/** Base of every polymorphic type in the engine. */
class CORE_API Object
{
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

	Object() = default;
	Object(const Object& copy) = delete;
	Object(Object&& move) = delete;
	virtual ~Object();

	///////////////////
	///   Methods   ///
public:

	/** Returns a pointer to the block header for this Object.
	* NOTE: Returns 'null' if this Object is not managed (or if it is still being constructed). */
	FORCEINLINE const MemoryBlockController* GetBlockController() const
	{
		if (_managedWithBlockController)
		{
			// MemoryBlockControllers are always constructed immediately before the value they control, so we just use some pointer arithmetic.
			return reinterpret_cast<const MemoryBlockController*>(this) - 1;
		}
		else
		{
			return nullptr;
		}
	}

	/** Returns a pointer to the block controller for this Object.
	* NOTE: Returns 'null' if this Object is not managed (or if it is still being constructed). */
	FORCEINLINE MemoryBlockController* GetBlockController()
	{
		auto blockController = static_cast<const Object*>(this)->GetBlockController();
		return const_cast<MemoryBlockController*>(blockController);
	}

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

	/** Whether this object is managed. If it is, you may access its block controller via 'GetBlockController()'. */
	bool _managedWithBlockController = false;

	// @TODO: Remove this in favor of managed references
	mutable Array<void*> _references;
};
