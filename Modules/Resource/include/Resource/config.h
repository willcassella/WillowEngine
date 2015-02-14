// config.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Reflection/Module.h>

///////////////////////////////
///   Build Configuration   ///

#ifdef RESOURCE_BUILD
	#define RESOURCE_API EXPORT
#else
	#define RESOURCE_API IMPORT
#endif

//////////////////////////
///   Initialization   ///

// @TODO: Update this to match other modules
RESOURCE_API const Module* Initialize_Resource();