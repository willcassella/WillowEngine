// MemoryBlock.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Memory/MemoryBlock.h"
#include "../../include/Core/Reflection/Variant.h"

///////////////////
///   Methods   ///

Variant MemoryBlockHeader::GetDataAsVariant() const
{
	/** Returning a Variant pointing to an uninitialized object isn't safe. */
	assert(this->Status != MemoryBlockStatus::Uninitialized);

	return Variant(this->GetData(), this->GetAllocatedType());
}
