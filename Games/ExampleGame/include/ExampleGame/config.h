// config.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/env.h>

///////////////////////////////
///   Build Configuration   ///

#ifdef EXAMPLEGAME_BUILD
	#define EXAMPLEGAME_API EXPORT
#else
	#define EXAMPLEGAME_API IMPORT
#endif
