// config.h - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/Core.h>

///////////////////////////////
///   Build Configuration   ///

#ifdef RESOURCE_BUILD
#	define RESOURCE_API EXPORT
#else
#	define RESOURCE_API IMPORT
#endif

#if defined THIS_MODULE_API
#	undef THIS_MODULE_API
#endif

#define THIS_MODULE_API RESOURCE_API
