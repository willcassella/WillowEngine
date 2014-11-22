// config.h
#pragma once

#include <cstdint>

///////////////////////////////
///   Build Configuration   ///

#ifdef LINK_STATIC
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

////////////////////////////////
///   Forward Declarations   ///

namespace Willow
{
	///////////////////
	///   Classes   ///

	// Basic
	class Console;
	class object;
		class String;

		// Containers
		template <typename T> class List;
		template <typename T> class Array;
		template <typename T> class Queue;
		template <typename T> class Stack;
		template <typename KeyType, typename ValueType> class Table;
		template <typename A, typename B> class Pair;

		// Math
		class Vec2;
		class Vec3;
		class Quat;
		class Mat4;

		// Reflection
		class Module;
		class Type;
			class Interface;
			class InterfaceType;
			class ClassType;
				class TemplateType;
			class PrimitiveType;
				class PointerType;
			class NonReflectedType;
		template <class OwnerType, typename FieldType> class Field;
		template <class OwnerType, typename PropertyType> class Property;

		// Reflection Utilities
		template <typename UserType> struct __type_info__;
		template <typename FirstType, typename ... RestTypes> struct __multiple_type_info__;
	
	//////////////////////
	///   Interfaces   ///

	interface IField;

	/////////////////////
	///   Functions   ///

	template <typename T> const Type& TypeInfo();
	template <typename ... Types> List<const Type&> MultipleTypeInfo();
}