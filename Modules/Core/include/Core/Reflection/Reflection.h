// Reflection.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <initializer_list>
#include "../config.h"
#include "../Forwards/Containers.h"
#include "../Forwards/Memory.h"
#include "../Forwards/Reflection.h"
#include "../STDE/TypeTraits.h"

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
		FORCEINLINE static auto Function() -> decltype((T::StaticTypeInfo))
		{
			using StorageT = decltype(T::StaticTypeInfo);
			using TypeInfoT = std::decay_t<StorageT>;

			CommonAsserts<TypeInfoT>();
				
			static_assert(std::is_const<StorageT>::value && std::is_object<StorageT>::value,
				"The 'StaticTypeInfo' static object must be a const value.");

			return T::StaticTypeInfo;
		}

		FORCEINLINE static auto Function(const T& value) -> decltype(value.T::GetType())
		{
			using ReturnT = decltype(value.T::GetType());
			using TypeInfoT = std::decay_t<ReturnT>;

			CommonAsserts<TypeInfoT>();

			static_assert(stde::is_reference_to_const<ReturnT>::value,
				"The 'GetType()' member function must return an immutable reference");
			
			return value.GetType();
		}

	private:

		template <typename TypeInfoT>
		FORCEINLINE static void CommonAsserts()
		{
			static_assert(std::is_base_of<TypeInfo, TypeInfoT>::value,
				"The 'StaticTypeInfo' static object must be a 'TypeInfo' object.");
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

		/** It is not possible to have an instance of 'void', so that Function is not necessary. */
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

	/** Implementation of 'TypeOf' for long double */
	template <>
	struct CORE_API TypeOf < long double > final
	{
	    /** Defined in 'Reflection/Reflection.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(long double /*value*/)
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

/** Retrieves the type information for the given type. */
template <typename T>
FORCEINLINE const auto& TypeOf()
{
	return Implementation::TypeOf<std::decay_t<T>>::Function();
}

/** Retrieves the type information for the given value.
* DO NOT OVERLOAD: Specialize struct 'Implementation::TypeOf'. */
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

/** Base reflection declarations for reflectable types.
* NOTE: In most cases you shouldn't use this directly, instead use one of the REFLECTABLE_X macros defined below. */
#define REFLECTION_DECL(T)									\
public:														\
	using TypeInfoType = T;									\
	static const TypeInfoType StaticTypeInfo;

/** Put this macro in the Information section of a struct you'd like to reflect.
* NOTE: Any struct that uses this macro must also use the 'BUILD_REFLECTION' macro in their source file. */
#define REFLECTABLE_STRUCT									\
	REFLECTION_DECL(::StructInfo)							\
	FORCEINLINE const ::StructInfo& GetType() const			\
	{														\
		return StaticTypeInfo;								\
	}

/** Put this macro in the Information section of a class you'd like to reflect.
* NOTE: Any class that uses this macro must also use the 'EXTENDS' macro in the Information section of their
* header, as well as the 'BUILD_REFLECTION' macro in their source file. */
#define REFLECTABLE_CLASS							\
	REFLECTION_DECL(::ClassInfo)					\
	const ::ClassInfo& GetType() const override		\
	{												\
		return StaticTypeInfo;						\
	}

/** Put this macro in the Information section of an interface you'd like to reflect.
* NOTE: Any interface that uses this macro @TODO: Finish documentation here */
#define REFLECTABLE_INTERFACE						\
	REFLECTION_DECL(::InterfaceInfo)

/** Put this macro in the global namespace, ideally in the same file that declares the enum.
* NOTE: This macro MUST be put in the global namespace. 
* NOTE: Any use of this macro must have a corresponding 'BUILD_ENUM_REFLECTION(e)' macro in an source file
* somewhere in the same module. */
#define REFLECTABLE_ENUM(API, E)							\
namespace Implementation									\
{															\
	template <>												\
	struct API TypeOf < E >	final							\
	{														\
		REFLECTION_DECL(::EnumInfo)							\
															\
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

/** Put this macro in the Information section of a class you'd like to reflect.
* NOTE: All reflectable classes must use this macro.
* 'T': The class which this class extends. */
#define EXTENDS(T)									\
public:												\
	using Base = T;

/** Put this macro in the Information section of every reflectable class that implements interfaces. */
#define IMPLEMENTS(...)										\
public:														\
	using Interfaces = ::stde::type_sequence<__VA_ARGS__>;
