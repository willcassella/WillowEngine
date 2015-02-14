// config.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "System.h"

///////////////////////////////
///   Build Configuration   ///

#if defined	CORE_BUILD
	#define CORE_API EXPORT
#else
	#define CORE_API IMPORT
#endif

//////////////////////////////
///   Module Information   ///

/** Defined in 'Reflection/Module.h' */
class Module;

namespace Core
{
	CORE_API const Module* GetModuleInfo();
}