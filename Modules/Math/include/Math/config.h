// config.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Core.h>

///////////////////////////////
///   Build configuration   ///

#if defined MATH_BUILD
#	define MATH_API EXPORT
#else
#	define MATH_API IMPORT
#endif

#if defined THIS_MODULE_API
#	undef THIS_MODULE_API
#endif

#define THIS_MODULE_API MATH_API
