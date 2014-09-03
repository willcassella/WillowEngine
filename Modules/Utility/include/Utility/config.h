// config.h
#pragma once

#ifdef CORE_STATIC
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

#ifdef CORE_BUILD
	#define CORE_API EXPORT
#else
	#define CORE_API IMPORT
#endif