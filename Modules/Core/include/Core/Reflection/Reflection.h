// Reflection.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
/** Many types in the reflection system are highly inter-dependent, so this
* header has forward-declarations for all of them */
#pragma once

#include <type_traits>
#include "../config.h"

////////////////////////////////
///   Forward-declarations   ///

/** Defined in 'TypeInfo.h' */
class TypeInfo;

/** Defined in 'StructInfo.h' */
class StructInfo;

/** Defined in 'ClassInfo.h' */
class ClassInfo;

/** Defined in 'InterfaceInfo.h' */
class InterfaceInfo;

/** Defined in 'VoidInfo.h' */
class VoidInfo;

/** Defined in 'Variant.h' */
struct Variant;

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Default implementation of 'TypeOf' */
	template <typename AnyType>
	struct TypeOf
	{
		FORCEINLINE static const TypeInfo& Function()
		{
			static_assert(!std::is_same<AnyType, Variant>::value, "'Variant' has no static type information");
			return AnyType::StaticTypeInfo;
		}

		FORCEINLINE static const TypeInfo& Function(const AnyType& value)
		{
			return value.GetType();
		}
	};
}

/////////////////////
///   Functions   ///

/** Defined in 'TypeInfo.h' */
template <typename TargetType, typename AnyType>
TargetType* Cast(AnyType& value);

/** Defined in 'TypeInfo.h' */
template <typename TargetType, typename AnyType>
const TargetType* Cast(const AnyType& value);

/** Retrieves the type information for the given type
* DO NOT OVERLOAD: Specialize struct 'Implementation::TypeOf' */
template <typename AnyType>
FORCEINLINE const TypeInfo& TypeOf()
{
	return Implementation::TypeOf<AnyType>::Function();
}

/** Retrieves the type information for the given value 
* DO NOT OVERLOAD: Specialize struct 'Implementation::TypeOf' */
template <typename AnyType>
FORCEINLINE const TypeInfo& TypeOf(const AnyType& value)
{
	return Implementation::TypeOf<AnyType>::Function(value);
}

//////////////////
///   Macros   ///

/** Put this macro in the Information section of a struct you'd like to reflect
* NOTE: Any struct that uses this macro must also use the 'STRUCT_REFLECTION' macro in their source file */
#define REFLECTABLE_STRUCT							\
public:												\
	static const ::StructInfo StaticTypeInfo;		\
	FORCEINLINE const ::StructInfo& GetType() const	\
	{												\
		return StaticTypeInfo;						\
	}

/** Put this macro in the Information section of a class you'd like to reflect
* NOTE: Any class that uses this macro must also use the 'EXTENDS' macro in the Information section of their
* header, as well as the 'CLASS_REFLECTION' macro in their source file */
#define REFLECTABLE_CLASS							\
public:												\
	static const ::ClassInfo StaticTypeInfo;		\
	const ::ClassInfo& GetType() const override		\
	{												\
		return StaticTypeInfo;						\
	}

/** Put this macro in the Information section of an interface you'd like to reflect
* NOTE: Any interface that uses this macro @TODO: Finish documentation here */
#define REFLECTABLE_INTERFACE						\
public:												\
	static const ::InterfaceInfo StaticTypeInfo;

/** Put this macro in the Information section of a class
* NOTE: All reflectable classes must use this macro 
* T: The class which this class extends */
#define EXTENDS(T)									\
public:												\
	typedef T Super;