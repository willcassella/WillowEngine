// config.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Reflection/Module.h>

///////////////////////////////
///   Build configuration   ///

#if defined MATH_BUILD
	#define MATH_API EXPORT
#else
	#define MATH_API IMPORT
#endif

//////////////////////////////
///   Module Information   ///

namespace Math
{
	MATH_API const Module* GetModuleInfo();
}