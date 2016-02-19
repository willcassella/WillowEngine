// MemoryBlock.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <atomic>
#include <cassert>
#include "../config.h"

/** Structure holding reference count information for a memory block. */
struct CORE_API ReferenceCounter final
{
	///////////////////////
	///   Information   ///
public:

	friend class Object;

	////////////////////////
	///   Constructors   ///
private:

	ReferenceCounter()
		: _numBorrows(0), _numWeakRefs(0)
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this object was destroyed. */
	FORCEINLINE bool IsDestroyed() const
	{
		return _destroyed;
	}

	/** Sets the object as destroyed. */
	FORCEINLINE void SetDestroyed()
	{
		assert(_numBorrows == 0 /* Object was destroyed while being borrowed. */);
		_destroyed = true;

		// If the object was just destroyed and there are no weak references, delete this.
		if (_numWeakRefs == 0)
		{
			delete this;
		}
	}

	/** Gets the total number of active references on this object. */
	FORCEINLINE uint32 GetTotalRefs() const
	{
		return this->GetNumBorrows() + this->GetNumWeakRefs();
	}

	/** Returns the number of active borrowed references. */
	FORCEINLINE uint32 GetNumBorrows() const
	{
		return _numBorrows;
	}

	/** Increments the number of borrowed references. */
	void AddBorrow()
	{
		++_numBorrows;
	}

	/** Decrements the number of borrowed references.
	* WARNING: The number of borrowed references must be greater than '0'. */
	void ReleaseBorrow()
	{
		assert(_numBorrows > 0 /* You can't decrement the borrow count below '0'. */);
		--_numBorrows;
	}

	/** Returns the number of weak references to this object. */
	FORCEINLINE uint32 GetNumWeakRefs() const
	{
		return _numWeakRefs;
	}

	/** Increments the number of weak references. */
	void AddWeakRef()
	{
		assert(!_destroyed /* You may not create a new reference to a destroyed object. */);
		++_numWeakRefs;
	}

	/** Decrements the number of weak references.
	* WARNING: The number of weak references must be greater than '0'. */
	void ReleaseWeakRef()
	{
		assert(_numWeakRefs > 0 /* You may not decrement the number of weak references below '0'. */);
		--_numWeakRefs;

		if (_destroyed && _numWeakRefs == 0)
		{
			delete this;
		}
	}

	////////////////
	///   Data   ///
private:

	bool _destroyed = false;
	std::atomic<uint32> _numBorrows;
	std::atomic<uint32> _numWeakRefs;
};
