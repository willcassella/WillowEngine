// MemoryBlock.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"
#include "../Forwards/Memory.h"
#include "../Forwards/Reflection.h"

/////////////////
///   Types   ///

/** Indicates the status of a memory block. */
enum class MemoryBlockStatus : byte
{
	/** The block is created, but it does not have a value.
	* The memory returned by 'GetData' will be zeroed out. */
	Uninitialized,
	
	/* The block is created, and the value has been constructed and is ready for use. */
	Valid,

	/* The block is created and may be used, but will be destroyed at the next call to 'MemoryManager::Sweep'. */
	MarkedForDestruction
};

/** Structure located at the start of every memory block. */
struct CORE_API MemoryBlockHeader final
{
	///////////////////////
	///   Information   ///
public:

	/** Only the MemoryManager is allowed to construct BlockHeaders. */
	friend MemoryManager;

	////////////////////////
	///   Constructors   ///
private:

	MemoryBlockHeader(const TypeInfo& type)
		: Status(MemoryBlockStatus::Uninitialized), _type(&type)
	{
		// All done
	}

	//////////////////
	///   Fields   ///
public:

	MemoryBlockStatus Status;

	///////////////////
	///   Methods   ///
public:

	FORCEINLINE const TypeInfo& GetAllocatedType() const
	{
		return *_type;
	}

	FORCEINLINE void* GetData() const
	{
		return const_cast<MemoryBlockHeader*>(this) + 1;
	}

	FORCEINLINE void MarkForDestruction()
	{
		if (Status != MemoryBlockStatus::Uninitialized)
		{
			Status = MemoryBlockStatus::MarkedForDestruction;
		}
	}

	Variant GetDataAsVariant() const;

	////////////////
	///   Data   ///
private:

	const TypeInfo* _type;
};
