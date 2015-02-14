// Reflection.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
/** Many types in the reflection system are highly inter-dependent, so this
* header has forward-declarations for all of them */
#pragma once

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

/** Defined in 'PrimitiveInfo.h' */
class PrimitiveInfo;

/** Defined in 'PointerInfo.h' */
class PointerInfo;

/** Defined in 'Reference.h' */
struct Reference;

/** Defined in 'Value.h' */
struct Value;

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Defined in 'Unpack.h' */
	template <typename TargetType>
	struct Unpack;

	/** Default implementation of 'TypeOf' */
	template <typename AnyType>
	struct TypeOf
	{
		FORCEINLINE static const TypeInfo& Function()
		{
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

/** Defined in 'Factory.h' */
template <typename AnyType>
Value StackFactory();

/** Defined in 'Factory.h' */
template <typename AnyType>
Reference HeapFactory();

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
* NOTE: Any struct that uses this macro must also use the 'BEGIN_STRUCT_REFLECTION' macro in their source file */
#define REFLECTABLE_STRUCT						\
public:											\
	static const StructInfo StaticTypeInfo;		\
	FORCEINLINE const StructInfo& GetType() const	\
	{											\
		return StaticTypeInfo;					\
	}

/** Put this macro in the Information section of a class you'd like to reflect
* NOTE: Any class that uses this macro must also use the' BEGIN_CLASS_REFLECTION' macro in their source file */
#define REFLECTABLE_CLASS						\
public:											\
	static const ClassInfo StaticTypeInfo;		\
	const ClassInfo& GetType() const override	\
	{											\
		return StaticTypeInfo;					\
	}

/** Put this macro in the Information section of an interface you'd like to reflect
* NOTE: Any interface that uses this macro @TODO: Finish documentation here */
#define REFLECTABLE_INTERFACE					\
public:											\
	static const InterfaceInfo StaticTypeInfo;

/** Put this macro in the Information section of a class which extends the given type
* NOTE: All reflectable classes must use this macro */
#define EXTENDS(T)								\
public:											\
	typedef T Super;

/* NOTE: Reflection registration macros are declared in 'Registration.h' */