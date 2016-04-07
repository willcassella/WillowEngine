// GTable.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Containers/Table.h>
#include "../GHandle.h"

namespace Willow
{
	/** A GTable is a table mapping instance IDs for GameObject types to values. */
	template <class KeyT, class ValueT>
	using GTable = Table<GHandle<KeyT>, ValueT>;
}
