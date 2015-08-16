// Reflection.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <initializer_list>
#include "../config.h"
#include "../Forwards/Core.h"
#include "../Forwards/Containers.h"
#include "../Forwards/Reflection.h"
#include "../STDExt/TypeTraits.h"

/////////////////
///   Types   ///

/** Types extending 'Proxy' should be though of as proxy types, and not used in any contexts other than
* interaction with reflection data. 
* In particular, they should not be used as fields or have any sort of long-term storage. */
struct Proxy {};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	//////////////////////////////////
	///   Generic Implementation   ///

	/** Generic implementation of 'TypeOf' */
	template <typename T>
	struct TypeOf final
	{
		FORCEINLINE static const auto& Function()
		{
			using ReturnT = decltype(T::StaticTypeInfo);
			using TypeInfoT = std::remove_const_t<ReturnT>;

			static_assert(std::is_const<ReturnT>::value && std::is_object<ReturnT>::value,
				"The 'StaticTypeInfo' static object must be a const value type");

			static_assert(std::is_base_of<TypeInfo, TypeInfoT>::value,
				"The 'StaticTypeInfo' static object must be a 'TypeInfo' object");

			return T::StaticTypeInfo;
		}

		FORCEINLINE static const auto& Function(const T& value)
		{
			using ReturnT = decltype(value.GetType());
			using TypeInfoT = std::decay_t<ReturnT>;

			static_assert(std::is_reference<ReturnT>::value && std::is_const<std::remove_reference_t<ReturnT>>::value,
				"The 'GetType()' member function must return an immutable reference");

			static_assert(std::is_base_of<TypeInfo, TypeInfoT>::value,
				"The 'GetType()' member function must return a 'TypeInfo' object");
			
			return value.GetType();
		}
	};

	/////////////////////////////
	///   Fundamental Types   ///

	/** Implementation of 'TypeOf' for void */
	template <>
	struct CORE_API TypeOf < void > final
	{
		/** Defined in 'Reflection/Reflection.cpp' */
		static const VoidInfo StaticTypeInfo;

		FORCEINLINE static const VoidInfo& Function()
		{
			return StaticTypeInfo;
		}

		/** It is not possible to an instance of 'void', so that Function is not necessary. */
	};

	/** Implementation of 'TypeOf' for std::nullptr_t */
	template <>
	struct CORE_API TypeOf < std::nullptr_t > final
	{
		/** Defined in 'Reflection/Reflection.cpp' */
		static const PointerInfo StaticTypeInfo;

		FORCEINLINE static const PointerInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PointerInfo& Function(std::nullptr_t /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	//////////////////////////
	///   PrimitiveTypes   ///

	/** Implementation of 'TypeOf' for bool */
	template <>
	struct CORE_API TypeOf < bool > final
	{
		/** Defined in 'Reflection/Reflection.cpp' */
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

	/** Implementation of 'TypeOf' for char */
	template <>
	struct CORE_API TypeOf < char > final
	{
		/** Defined in 'Reflection/Reflection.cpp' */
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

	/** Implementation of 'TypeOf' for byte */
	template <>
	struct CORE_API TypeOf < byte > final
	{
		/** Defined in 'Reflection/Reflection.cpp' */
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

	/** Implementation of 'TypeOf' for int16 */
	template <>
	struct CORE_API TypeOf < int16 > final
	{
		/** Defined in 'Reflection/Reflection.cpp' */
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

	/** Implementation of 'TypeOf' for int32 */
	template <>
	struct CORE_API TypeOf < int32 > final
	{
		/** Defined in 'Reflection/Reflection.cpp' */
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

	/** Implementation of 'TypeOf' for int64 */
	template <>
	struct CORE_API TypeOf < int64 > final
	{
		/** Defined in 'Reflection/Reflection.cpp' */
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

	/** Implementation of 'TypeOf' for uint16 */
	template <>
	struct CORE_API TypeOf < uint16 > final
	{
		/** Defined in 'Reflection/Reflection.cpp' */
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

	/** Implementation of 'TypeOf' for uint32 */
	template <>
	struct CORE_API TypeOf < uint32 > final
	{
		/** Defined in 'Reflection/Reflection.cpp' */
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

	/** Implementation of 'TypeOf' for uint64 */
	template <>
	struct CORE_API TypeOf < uint64 > final
	{
		/** Defined in 'Reflection/Reflection.cpp' */
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

	/** Implementation of 'TypeOf' for float */
	template <>
	struct CORE_API TypeOf < float > final
	{
		/** Defined in 'Reflection/Reflection.cpp' */
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

	/** Implementation of 'TypeOf' for double */
	template <>
	struct CORE_API TypeOf < double > final
	{
		/** Defined in 'Reflection/Reflection.cpp' */
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

	/** Implementation of 'TypeOf' for pointers */
	template <typename PointedT>
	struct TypeOf < PointedT* > final
	{
		/** Defined in 'Reflection/PointerInfo.h' */
		static const PointerInfo StaticTypeInfo;

		FORCEINLINE static const PointerInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PointerInfo& Function(PointedT* /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** Implementation of 'TypeOf' for arrays (decayed to pointers) */
	template <typename T, std::size_t Size>
	struct TypeOf < T[Size] > final
	{
		FORCEINLINE static const PointerInfo& Function()
		{
			return TypeOf<T*>::Function();
		}

		FORCEINLINE static const PointerInfo& Function(T* value)
		{
			return TypeOf<T*>::Function(value);
		}

		// @TODO: Why is this necessary?
		FORCEINLINE static const PointerInfo& Function(const T* value)
		{
			return TypeOf<const T*>::Function(value);
		}
	};

	////////////////////////
	///   Struct Types   ///

	/** Implementation of 'TypeOf' for String */
	template <>
	struct CORE_API TypeOf < String > final
	{
		/** Defined in 'Reflection/Reflection.cpp' */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const StructInfo& Function(const String& /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** Implementation of 'TypeOf' for std::intializer_list */
	template <typename T>
	struct TypeOf < std::initializer_list<T> > final
	{
		/** Defined in 'Reflection/StructInfo.h' */
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

	/** Implementation of 'TypeOf' for Array */
	template <typename T>
	struct TypeOf < Array<T> > final
	{
		/** Defined in 'Reflection/StructInfo.h' */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const StructInfo& Function(const Array<T>& /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** Implementation of 'TypeOf' for List */
	template <typename T>
	struct TypeOf < List<T> > final
	{
		/** Defined in 'Reflection/StructInfo.h' */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const StructInfo& Function(const List<T>& /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** Implementation of 'TypeOf' for Queue */
	template <typename T>
	struct TypeOf < Queue<T> > final
	{
		/** Defined in 'Reflection/StructInfo.h' */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const StructInfo& Function(const Queue<T>& /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** Implementation of 'TypeOf' for Stack */
	template <typename T>
	struct TypeOf < Stack<T> > final
	{
		/** Defined in 'Reflection/StructInfo.h' */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const StructInfo& Function(const Stack<T>& /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** Implementation of 'TypeOf' for Table */
	template <typename KeyT, typename ValueT>
	struct TypeOf < Table<KeyT, ValueT> > final
	{
		/** Defined in 'Reflection/StructInfo.h' */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const StructInfo& Function(const Table<KeyT, ValueT>& /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** Implementation of 'TypeOf' for Pair */
	template <typename A, typename B>
	struct TypeOf < Pair<A, B> > final
	{
		/** Defined in 'Reflection/StructInfo.h' */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const StructInfo& Function(const Pair<A, B>& /*value*/)
		{
			return StaticTypeInfo;
		}
	};
}

/////////////////////
///   Functions   ///

/** Retrieves the type information for the given type.
* DO NOT OVERLOAD: Specialize struct 'Implementation::TypeOf'. */
template <typename T>
FORCEINLINE const auto& TypeOf()
{
	return Implementation::TypeOf<std::decay_t<T>>::Function();
}

/** Retrieves the type information for the given value.
* DO NOT OVERLOAD: Specialize struct 'Implementation::GetType'. */
template <typename T>
FORCEINLINE const auto& TypeOf(const T& value)
{
	return Implementation::TypeOf<T>::Function(value);
}

/////////////////
///   Types   ///

/** Aliases the base type of the given class. */
template <class ClassT>
using BaseTypeOf = typename ClassT::Base;

/** Aliases the Interface sequence of the given class. */
template <class ClassT>
using InterfaceTypesOf = typename ClassT::Interfaces;

/** Aliases the type of TypeInfo class that the given type uses. */
template <typename T>
using TypeInfoTypeOf = std::decay_t<decltype(TypeOf<T>())>;

//////////////////
///   Macros   ///

// @TODO: Documentation
#define REFLECTABLE_ENUM(E)									\
namespace Implementation									\
{															\
	template <>												\
	struct THIS_MODULE_API TypeOf < E >	final				\
	{														\
		static const ::EnumInfo StaticTypeInfo;				\
		FORCEINLINE static const ::EnumInfo& Function()		\
		{													\
			return StaticTypeInfo;							\
		}													\
		FORCEINLINE static const ::EnumInfo& Function(E)	\
		{													\
			return StaticTypeInfo;							\
		}													\
	};														\
}

/** Put this macro in the Information section of a struct you'd like to reflect.
* NOTE: Any struct that uses this macro must also use the 'BUILD_REFLECTION' macro in their source file. */
#define REFLECTABLE_STRUCT										\
public:															\
	static const ::StructInfo StaticTypeInfo;					\
	FORCEINLINE const ::StructInfo& GetType() const				\
	{															\
		return StaticTypeInfo;									\
	}

/** Put this macro in the Information section of a class you'd like to reflect.
* NOTE: Any class that uses this macro must also use the 'EXTENDS' macro in the Information section of their
* header, as well as the 'BUILD_REFLECTION' macro in their source file. */
#define REFLECTABLE_CLASS							\
public:												\
	static const ::ClassInfo StaticTypeInfo;		\
	const ::ClassInfo& GetType() const override		\
	{												\
		return StaticTypeInfo;						\
	}

/** Put this macro in the Information section of an interface you'd like to reflect.
* NOTE: Any interface that uses this macro @TODO: Finish documentation here */
#define REFLECTABLE_INTERFACE						\
public:												\
	static const ::InterfaceInfo StaticTypeInfo;

/** Put this macro in the Information section of a class you'd like to reflect.
* NOTE: All reflectable classes must use this macro.
* 'T': The class which this class extends. */
#define EXTENDS(T)									\
public:												\
	using Base = T;

/** Put this macro in the Information section of every reflectable class that implements interfaces. */
#define IMPLEMENTS(...)										\
public:														\
	using Interfaces = stdEXT::type_sequence<__VA_ARGS__>;
