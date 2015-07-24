// config.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "env.h"

///////////////////////////////
///   Build Configuration   ///

#if defined	CORE_BUILD
#	define CORE_API EXPORT
#else
#	define CORE_API IMPORT
#endif

#if defined THIS_MODULE
#	undef THIS_MODULE
#endif

#if defined THIS_MODULE_API
#	undef THIS_MODULE_API
#endif

#define THIS_MODULE_API CORE_API
