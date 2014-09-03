// config.h
#pragma once

#ifdef ENGINE_STATIC
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

#ifdef ENGINE_BUILD
	#define ENGINE_API EXPORT
#else
	#define ENGINE_API IMPORT
#endif