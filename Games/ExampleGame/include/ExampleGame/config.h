// config.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Reflection/Module.h>

///////////////////////////////
///   Build Configuration   ///

#ifdef EXAMPLEGAME_BUILD
	#define EXAMPLEGAME_API EXPORT
#else
	#define EXAMPLEGAME_API IMPORT
#endif