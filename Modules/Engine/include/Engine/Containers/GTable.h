// GTable.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Containers/Table.h>
#include "../Handle.h"

namespace willow
{
	/** A GTable is a table mapping instance IDs for GameObject types to values. */
	template <class KeyT, class ValueT>
	using GTable = Table<Handle<KeyT>, ValueT>;
}
