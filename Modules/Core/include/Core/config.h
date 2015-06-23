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
#define THIS_MODULE CORE_API

//////////////////////////////
///   Module Information   ///

/** Defined in 'Reflection/Module.h' */
class Module;

namespace Core
{
	/** Gets module information for the 'Core' module */
	CORE_API const Module* GetModuleInfo();
}