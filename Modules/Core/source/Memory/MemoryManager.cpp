// MemoryManager.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <utility>
#include "../../include/Core/Memory/MemoryManager.h"
#include "../../include/Core/Reflection/ClassInfo.h"

////////////////////////
///   Constructors   ///

MemoryManager::~MemoryManager()
{
	// All memory managed by the memory manager should have been freed by the time it is shut down
	// TODO: On MSVC this assertion never fails, even when the condition is false. I should figure out why.
	assert(_blocks.IsEmpty());
}

///////////////////
///   Methods   ///

MemoryBlockHeader* MemoryManager::AllocateNew(const TypeInfo& type)
{
	auto addr = (MemoryBlockHeader*)calloc(sizeof(MemoryBlockHeader) + type.GetSize(), 1);

	// Construct the memory block header
	new (addr) MemoryBlockHeader(type);

	// Add the block and return it
	_blocks.Add(addr);
	return addr;
}

void MemoryManager::Sweep()
{
	// Deconstruct values in blocks marked for destruction
	for (auto& block : _blocks)
	{
		if (block->Status == MemoryBlockStatus::MarkedForDestruction)
		{
			Variant value = block->GetDataAsVariant();

			// If the block contains a value of type 'Object', indicate that referencing clearing has already occurred
			if (auto pValue = Cast<Object>(value))
			{
				pValue->ReferenceClearStatus = Object::ReferenceClearState::Complete;
			}

			// Deconstruct value, and free block
			value.Destroy();
			free(block);
			block = nullptr;
		}
	}

	// Remove all nulled block pointers
	_blocks.DeleteAll(nullptr);
}

void MemoryManager::ClearReferences(const void* /*addr*/)
{
	// Do nothing, this needs to be implemented
}

void MemoryManager::ClearReferences(const Array<const void*>& /*addrs*/)
{
	// Do nothing, this needs to be implemented
}
