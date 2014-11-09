// config.h
#pragma once

///////////////////////////////
///   Build Configuration   ///

#ifdef CORE_STATIC
	#define IMPORT
	#define EXPORT
#else
	#ifdef WIN32
		#define IMPORT __declspec(dllimport)
		#define EXPORT __declspec(dllexport)
	#else
		#define IMPORT
		#define EXPORT
	#endif
#endif

#ifdef CORE_BUILD
	#define CORE_API EXPORT
#else
	#define CORE_API IMPORT
#endif

////////////////////
///   Includes   ///

#include <Utility\Reflection\Reflection.h>