// config.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Core.h>

///////////////////////////////
///   Build Configuration   ///

#ifdef ENGINE_BUILD
#	define ENGINE_API EXPORT
#else
#	define ENGINE_API IMPORT
#endif

#if defined THIS_MODULE_API
#	undef THIS_MODULE_API
#endif

#define THIS_MODULE_API ENGINE_API