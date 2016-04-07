// config.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/config.h>

///////////////////////////////
///   Build Configuration   ///

#ifdef GLRENDER_BUILD
#	define GLRENDER_API EXPORT
#else
#	define GLRENDER_API IMPORT
#endif
