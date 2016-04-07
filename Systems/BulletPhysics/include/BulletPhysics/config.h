// config.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/env.h>

///////////////////////////////
///   Build Configuration   ///

#ifdef BULLETPHYSICS_BUILD
#	define BULLETPHYSICS_API EXPORT
#else
#	define BULLETPHYSICS_API IMPORT
#endif
