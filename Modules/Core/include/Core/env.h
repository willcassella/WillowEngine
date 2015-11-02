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
// char is still char (ONLY used for characters, prefer 'Char')
using byte = std::uint8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;
// float is still float
// double is still double

/** The type of character used for strings. */
using Char = char;

/** A c-style string of characters. */
using CString = const Char*;

/** Note on 'void*' vs 'byte*':
* In some parts of the engine you can see 'void*' and 'byte*' used.
* Instances of 'byte*' indicate that the address should be treated as raw memory, which may or may not contain an instance of a type (usually not).
* Instances of 'void*' indicate that the address should be treated as a type-erased value, and an accompanied 'const TypeInfo*' should be passed along.
* In general, 'void*' + 'const TypeInfo*' pairs will be wrapped in the 'Variant' or 'ImmutableVariant' types, so you really don't have to worry about this. */

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
* Still, you should prefer using 'this' over 'self'. */
#define self (*this)
