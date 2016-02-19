// config.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "env.h"

///////////////////////////////
///   Build Configuration   ///

#if defined	CORE_BUILD
#	define CORE_API EXPORT
#else
#	define CORE_API IMPORT
#endif
