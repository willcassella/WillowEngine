// env.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
/** All macros for determining compiler and build environment go here */
#pragma once

#include <cstdint>

/////////////////////////////
///   Build Information   ///

/** Determine linkage */
#if defined LINK_STATIC
	/** Modules are being linked statically (as .lib or .ar files) */
#	define IMPORT
#	define EXPORT
#else
	/** Modules are being linked dynamically (as .dll or .so files) */
#	if defined WINDOWS
		/** The engine is being compiled on Windows */
#		define IMPORT __declspec(dllimport)
#		define EXPORT __declspec(dllexport)
#	else
		/** We're on OSX or Linux or something, so __declspec(blah blah) isn't needed */
#		define IMPORT
#		define EXPORT
#	endif
#endif

//////////////////////
///   Primitives   ///

// bool is still bool
// char is still char (ONLY used for characters)
typedef std::uint8_t byte;
typedef std::int16_t int16;
typedef std::int32_t int32;
typedef std::int64_t int64;
typedef std::uint16_t uint16;
typedef	std::uint32_t uint32;
typedef std::uint64_t uint64;
// float is still float
// double is still double

/** Determine numeric size of pointers */
#if BITS_32
	typedef uint32 PointerT;
#elif BITS_64
	typedef uint64 PointerT;
#endif

//////////////////
///   Macros   ///

/** Inline macro */
#if defined _MSC_VER
	/** We're on MSVC, so use the __forceinline specifier */
#	define FORCEINLINE __forceinline
#elif defined __clang__ || defined __GNUC__
	/** We're on clang or gcc, so use the __attribute__((always_inline)) attribute */
#	define FORCEINLINE inline __attribute__((always_inline))
#else
	/** We're on some unknown compiler, so just use normal inline */
#	define FORCEINLINE inline
#endif

/** Shortcut for dereferencing 'this', useful for calling operators on self and returning reference to self in a clean way.
* Still, you should prefer using 'this' over 'This'. */
#define This (*this)