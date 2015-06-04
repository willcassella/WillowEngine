// Reflection.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
/** Many types in the reflection system are highly inter-dependent, so this
* header has forward-declarations for all of them */
#pragma once

#include <type_traits>
#include <initializer_list> // @TODO: Check if this is necessary
#include "../config.h"

////////////////////////////////
///   Forward-declarations   ///

/** Defined in 'TypeInfo.h' */
class TypeInfo;

/** Defined in 'VoidInfo.h' */
class VoidInfo;

/** Defined in 'PrimitiveInfo.h' */
class PrimitiveInfo;

/** Defined in 'PointerInfo.h' */
class PointerInfo;

/** Defined in 'StructInfo.h' */
class StructInfo;

/** Defined in 'ClassInfo.h' */
class ClassInfo;

/** Defined in 'InterfaceInfo.h' */
class InterfaceInfo;

/** Defined in 'Variant.h' */
struct Variant;

/** Defined in 'Variant.h' */
struct ImmutableVariant;

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	//////////////////////////////////
	///   Generic Implementation   ///

	/** Default implementation of 'TypeOf' */
	template <typename AnyType>
	struct TypeOf
	{
		FORCEINLINE static const auto& Function()
		{
			using ReturnType = decltype(AnyType::StaticTypeInfo);
			using TypeInfoType = typename std::remove_const<ReturnType>::type;

			static_assert(std::is_const<ReturnType>::value && std::is_object<ReturnType>::value,
				"The 'StaticTypeInfo' static object must be a const value type");

			static_assert(std::is_base_of<TypeInfo, TypeInfoType>::value,
				"The 'StaticTypeInfo' static object must be a 'TypeInfo' object");

			return AnyType::StaticTypeInfo;
		}

		FORCEINLINE static const auto& Function(const AnyType& value)
		{
			using ReturnType = decltype(value.GetType());
			using TypeInfoType = typename std::decay<ReturnType>::type;

			static_assert(std::is_reference<ReturnType>::value && std::is_const<typename std::remove_reference<ReturnType>::type>::value,
				"The 'GetType' member function must return an immutable reference");

			static_assert(std::is_base_of<TypeInfo, TypeInfoType>::value,
				"The 'GetType()' member function must return a 'TypeInfo' object");
			
			return value.GetType();
		}
	};

	/////////////////////////////
	///   Fundamental Types   ///

	/** TypeOf for 'void' */
	template <>
	struct TypeOf < void >
	{
		/** Defined in 'Reflection.cpp' */
		static const VoidInfo StaticTypeInfo;

		FORCEINLINE static const VoidInfo& Function()
		{
			return StaticTypeInfo;
		}

		/** It is not possible to have type data for an instance of 'void', so that Function is not necessary */
	};

	//////////////////////////
	///   PrimitiveTypes   ///

	/** TypeInfo for bool */
	template <>
	struct CORE_API TypeOf < bool >
	{
		/** Defined in 'Reflection.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(bool /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for char */
	template <>
	struct CORE_API TypeOf < char >
	{
		/** Defined in 'Reflection.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(char /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for byte */
	template <>
	struct CORE_API TypeOf < byte >
	{
		/** Defined in 'Reflection.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(byte /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for 16-bit integer */
	template <>
	struct CORE_API TypeOf < int16 >
	{
		/** Defined in 'Reflection.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(int16 /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for 32-bit integer */
	template <>
	struct CORE_API TypeOf < int32 >
	{
		/** Defined in 'Reflection.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(int32 /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for 64-bit integer */
	template <>
	struct CORE_API TypeOf < int64 >
	{
		/** Defined in 'Reflection.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(int64 /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for 16-bit unsigned integer */
	template <>
	struct CORE_API TypeOf < uint16 >
	{
		/** Defined in 'Reflection.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(uint16 /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for 32-bit unsigned integer */
	template <>
	struct CORE_API TypeOf < uint32 >
	{
		/** Defined in 'Reflection.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(uint32 /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for a 64-bit unsigned integer */
	template <>
	struct CORE_API TypeOf < uint64 >
	{
		/** Defined in 'Reflection.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(uint64 /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for a float */
	template <>
	struct CORE_API TypeOf < float >
	{
		/** Defined in 'Reflection.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(float /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for a double */
	template <>
	struct CORE_API TypeOf < double >
	{
		/** Defined in 'Reflection.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(double /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for pointers */
	template <typename PointedType>
	struct TypeOf < PointedType* >
	{
		/** Defined in 'PointerInfo.h' */
		static const PointerInfo StaticTypeInfo;

		FORCEINLINE static const PointerInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PointerInfo& Function(PointedType* /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	////////////////////////
	///   Struct Types   ///

	/** TypeOf for std::intializer_list */
	template <typename T>
	struct TypeOf < std::initializer_list<T> >
	{
		/** Defined in 'StructInfo.h' */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const StructInfo& Function(const std::initializer_list<T>& /*value*/)
		{
			return StaticTypeInfo;
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

/** r-value references cannot be safely casted */
template <typename TargetType, typename AnyType>
const TargetType* Cast(AnyType&& value) = delete;

/** Retrieves the type information for the given type
* DO NOT OVERLOAD: Specialize struct 'Implementation::TypeOf' */
template <typename AnyType>
FORCEINLINE const auto& TypeOf()
{	
	return Implementation::TypeOf<typename std::remove_const<AnyType>::type>::Function();
}

/** Retrieves the type information for the given value 
* DO NOT OVERLOAD: Specialize struct 'Implementation::TypeOf' */
template <typename AnyType>
FORCEINLINE const auto& TypeOf(const AnyType& value)
{
	return Implementation::TypeOf<AnyType>::Function(value);
}

//////////////////
///   Macros   ///

/** Put this macro in the Information section of a struct you'd like to reflect
* NOTE: Any struct that uses this macro must also use the 'STRUCT_REFLECTION' macro in their source file */
#define REFLECTABLE_STRUCT										\
public:															\
	static const ::StructInfo StaticTypeInfo;					\
																\
	/** Returns the reflection information for this struct */	\
	FORCEINLINE const ::StructInfo& GetType() const				\
	{															\
		return StaticTypeInfo;									\
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
	using Super = T;
