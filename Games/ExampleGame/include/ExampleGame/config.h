// config.h - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Core.h>

///////////////////////////////
///   Build Configuration   ///

#ifdef EXAMPLEGAME_BUILD
	#define EXAMPLEGAME_API EXPORT
#else
	#define EXAMPLEGAME_API IMPORT
#endif

#if defined THIS_MODULE_API
#	undef THIS_MODULE_API
#endif

#define THIS_MODULE_API EXAMPLEGAME_API
