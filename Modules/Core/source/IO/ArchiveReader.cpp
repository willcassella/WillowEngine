// ArchiveReader.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/IO/ArchiveReader.h"

////////////////////////
///   Constructors   ///

UnresolvedArchiveReferenceException::UnresolvedArchiveReferenceException(ArchiveRefID refID)
	: Exception{ "Could not resolve reference in Archive: @", refID }
{
	// All done
}
