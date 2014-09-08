// config.h
#pragma once

///////////////////////////////
///   Build Configuration   ///

#ifdef UTILITY_STATIC
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

#ifdef UTILITY_BUILD
	#define UTILITY_API EXPORT
#else
	#define UTILITY_API IMPORT
#endif

///////////////////////
///   Definitions   ///

#define interface class
typedef unsigned int uint;