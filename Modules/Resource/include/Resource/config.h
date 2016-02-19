// config.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/env.h>

///////////////////////////////
///   Build Configuration   ///

#ifdef RESOURCE_BUILD
#	define RESOURCE_API EXPORT
#else
#	define RESOURCE_API IMPORT
#endif
