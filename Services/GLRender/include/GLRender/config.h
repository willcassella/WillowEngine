// config.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/config.h>

///////////////////////////////
///   Build Configuration   ///

#ifdef GLRENDER_BUILD
#	define GLRENDER_API EXPORT
#else
#	define GLRENDER_API IMPORT
#endif

#if defined THIS_MODULE_API
#	undef THIS_MODULE_API
#endif

#define THIS_MODULE_API GLRENDER_API
