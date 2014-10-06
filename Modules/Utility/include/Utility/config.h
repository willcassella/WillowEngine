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

#define This (*this)

// char is still char
typedef short int16;
typedef int int32;
// long is not used
typedef __int64 int64;
typedef unsigned char byte;
typedef unsigned short uint16;
typedef unsigned int uint32;
// unsigned long is not used