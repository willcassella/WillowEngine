// config.h
#pragma once

///////////////////////////////
///   Build Configuration   ///

#ifdef EXAMPLEGAME_STATIC
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

#ifdef EXAMPLEGAME_BUILD
	#define EXAMPLEGAME_API EXPORT
#else
	#define EXAMPLEGAME_API IMPORT
#endif

////////////////////
///   Includes   ///

#include <Utility\Reflection\Reflection.h>