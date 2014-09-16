// config.h
#pragma once

///////////////////////////////
///   Build Configuration   ///

#ifdef RESOURCE_STATIC
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

#ifdef RESOURCE_BUILD
	#define RESOURCE_API EXPORT
#else
	#define RESOURCE_API IMPORT
#endif