// config.h
#pragma once

///////////////////////////////
///   Build Configuration   ///

#ifdef RENDER_STATIC
	#define IMPORT extern
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

#ifdef RENDER_BUILD
	#define RENDER_API EXPORT
#else
	#define RENDER_API IMPORT
#endif

////////////////////
///   Includes   ///

#include <Utility\Reflection\Reflection.h>