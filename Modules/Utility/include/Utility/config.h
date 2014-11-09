// config.h
#pragma once

#include <cstdint>

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

// bool is still bool
// char is still char
typedef int8_t byte;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef uint8_t ubyte;
typedef uint16_t uint16;
typedef	uint32_t uint32;
typedef uint64_t uint64;
// float is still float
// double is still double

// NOTE: All dependant modules should include <Utility\Reflection\Reflection.h> in their config files