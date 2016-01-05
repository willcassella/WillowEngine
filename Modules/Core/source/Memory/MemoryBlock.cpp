// MemoryBlock.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Memory/MemoryBlock.h"
#include "../../include/Core/Reflection/Variant.h"

///////////////////
///   Methods   ///

Variant MemoryBlockController::GetDataAsVariant()
{
	/** Returning a Variant pointing to an uninitialized or destroyed object isn't safe. */
	assert(this->_status == MemoryBlockValueStatus::Constructed);
	return Variant{ this->GetData(), this->GetAllocatedType() };
}

ImmutableVariant MemoryBlockController::GetDataAsVariant() const
{
	/** Returning a Variant pointing to an uninitialized or destroyed object isn't safe. */
	assert(this->_status == MemoryBlockValueStatus::Constructed);
	return ImmutableVariant{ this->GetData(), this->GetAllocatedType() };
}

void MemoryBlockController::Destroy()
{
	assert(this->GetRefCounter().GetNumOwnerRefs() == 0);
	assert(this->GetRefCounter().GetNumBorrowedRefs() == 0);
	assert(this->GetStatus() == MemoryBlockValueStatus::Constructed);

	this->GetAllocatedType().GetDestructor()(this->GetData());
	_status = MemoryBlockValueStatus::Destroyed;
}
