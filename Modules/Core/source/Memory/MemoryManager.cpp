// MemoryManager.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <utility>
#include "../../include/Core/Memory/MemoryManager.h"
#include "../../include/Core/Reflection/ClassInfo.h"

////////////////////////
///   Constructors   ///

MemoryManager::~MemoryManager()
{
	for (auto& block : _blocks)
	{
		assert(block->GetStatus() == MemoryBlockValueStatus::Destroyed || block->GetStatus() == MemoryBlockValueStatus::Uninitialized);
		free(block);
	}
}

///////////////////
///   Methods   ///

MemoryBlockController* MemoryManager::AllocateNew(const TypeInfo& type)
{
	auto addr = static_cast<MemoryBlockController*>(calloc(sizeof(MemoryBlockController) + type.GetSize(), 1));

	// Construct the memory block header
	new (addr) MemoryBlockController(type);

	// Add the block and return it
	_blocks.Add(addr);
	return addr;
}

void MemoryManager::Sweep()
{
	// Free blocks that may be destroyed
	for (auto& block : _blocks)
	{
		if (block->GetStatus() == MemoryBlockValueStatus::Destroyed)
		{
			const auto& refCounter = block->GetRefCounter();

			if (refCounter.GetTotalRefs() == 0)
			{
				free(block);
				block = nullptr;
			}
		}
	}

	// Remove all nulled block pointers
	_blocks.DeleteAll(nullptr);
}
