// MemoryManager.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Forwards/Core.h"
#include "../Containers/Array.h"
#include "MemoryBlock.h"

struct CORE_API MemoryManager final
{
	///////////////////////
	///   Information   ///
public:

	/** The MemoryManager singleton is part of the Application singleton. */
	friend Application;

	////////////////////////
	///   Constructors   ///
private:

	MemoryManager() = default;
	MemoryManager(const MemoryManager& copy) = delete;
	MemoryManager(MemoryManager&& move) = delete;
	~MemoryManager();

	///////////////////
	///   Methods   ///
public:

	/** Returns all memory blocks in the Manager. */
	FORCEINLINE const Array<MemoryBlockController*>& GetAllBlocks()
	{
		return _blocks;
	}

	/** Allocates and zeroes a memory block for the given type, but DOES NOT construct the value. 
	* NOTE: The status of the returned memory block is "Uninitialized". */
	MemoryBlockController* AllocateNew(const TypeInfo& type);

	/** Destroys and frees unused blocks. */
	void Sweep();

	/////////////////////
	///   Operators   ///
private:

	MemoryManager& operator=(const MemoryManager& copy) = delete;
	MemoryManager& operator=(MemoryManager&& move) = delete;

	////////////////
	///   Data   ///
private:

	Array<MemoryBlockController*> _blocks;
};
