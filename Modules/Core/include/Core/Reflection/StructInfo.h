// StructInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Containers/List.h"
#include "../Containers/Queue.h"
#include "../Containers/Stack.h"
#include "../Containers/Tuple.h"
#include "../Containers/Table.h"
#include "CompoundInfo.h"

/////////////////
///   Types   ///

/** Type information for structs */
class CORE_API StructInfo : public CompoundInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(CompoundInfo);

	////////////////////////
	///   Constructors   ///
public:

	/** Creates reflection information for the given struct
	* NOTE: Do not use this outside of the registration function for a struct 
	* 'name' - The fully-qualified name of the struct */
	template <class StructT>
	static StructInfo Create(CString name)
	{		
		StructT* dummy = nullptr;
		return StructInfo(dummy, name);
	}

	// @TODO: Documentation
	template <template <typename ... DependentT> class StructT, typename ... DependentT>
	static StructInfo CreateTemplate(CString name)
	{
		StructT<DependentT...>* dummy = nullptr;
		return StructInfo(dummy, name); // @TODO: Do more with this
	}

protected:

	// @TODO: Documentation
	template <class StructT>
	StructInfo(StructT* dummy, CString name)
		: Super(dummy, name)
	{
		static_assert(!std::is_polymorphic<StructT>::value, "Structs may not be polymorphic");
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this type is castable (via 'reinterpret_cast') to the given type */
	bool IsCastableTo(const TypeInfo& type) const override;

	////////////////
	///   Data   ///
private:

	Array<TypeIndex> _dependentTypes;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Register TypeInfo for std::intializer_list */
	template <typename T>
	const StructInfo TypeOf<std::initializer_list<T>>::StaticTypeInfo =
		StructInfo::CreateTemplate<std::initializer_list, T>("std::initializer_list");

	/** Register TypeInfo for 'Array' */
	template <typename T>
	const StructInfo TypeOf<Array<T>>::StaticTypeInfo =
		StructInfo::CreateTemplate<Array, T>("Array");

	/** TypeOf for List */
	template <typename T>
	struct TypeOf < List<T> >
	{
		/** Defined below */
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

	/** Register TypeInfo for List */
	template <typename T>
	const StructInfo TypeOf<List<T>>::StaticTypeInfo = 
		StructInfo::CreateTemplate<List, T>("List");

	/** TypeOf for Queue */
	template <typename T>
	struct TypeOf < Queue<T> >
	{
		/** Defined below */
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

	/** Register TypeInfo for Queue */
	template <typename T>
	const StructInfo TypeOf<Queue<T>>::StaticTypeInfo =
		StructInfo::CreateTemplate<Queue, T>("Queue");

	/** TypeOf for Stack */
	template <typename T>
	struct TypeOf < Stack<T> >
	{
		/** Defined below */
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

	/** Register TypeInfo for Stack */
	template <typename T>
	const StructInfo TypeOf<Stack<T>>::StaticTypeInfo = 
		StructInfo::CreateTemplate<Stack, T>("Stack");

	/** TypeOf for Table */
	template <typename KeyT, typename ValueT>
	struct TypeOf < Table<KeyT, ValueT> >
	{
		/** Defined below */
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

	/** Register TypeInfo for Table */
	template <typename KeyT, typename ValueT>
	const StructInfo TypeOf<Table<KeyT, ValueT>>::StaticTypeInfo = 
		StructInfo::CreateTemplate<Table, KeyT, ValueT>("Table");

	/** TypeOf for Pair */
	template <typename A, typename B>
	struct TypeOf < Pair<A, B> >
	{
		/** Defined below */
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

	/** Register TypeInfo for Pair */
	template <typename A, typename B>
	const StructInfo TypeOf<Pair<A, B>>::StaticTypeInfo = 
		StructInfo::CreateTemplate<Pair, A, B>("Pair");

	/** TypeOf for Tuple */
	template <typename ... T>
	struct TypeOf < Tuple<T...> >
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const StructInfo& Function(const Tuple<T...>& /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for Tuple */
	template <typename ... T>
	const StructInfo TypeOf<Tuple<T...>>::StaticTypeInfo =
		StructInfo::CreateTemplate<Tuple, T...>("Tuple");
}

//////////////////
///   Macros   ///

/** Put this macro in the source file of a struct you'd like to reflect
* NOTE: The struct must use the 'REFLECTABLE_STRUCT' flag in its "Information" section */
#define STRUCT_REFLECTION(T) const ::StructInfo T::StaticTypeInfo = ::StructInfo::Create<T>(#T)

/** Put this macro in the header file a struct template you'd like to reflect
* NOTE: The struct must use the 'REFLECTABLE_STRUCT' flag in its "Information" section */
#define TEMPLATE_STRUCT_REFLECTION(T, ...) const ::StructInfo T<__VA_ARGS__>::StaticTypeInfo = ::StructInfo::CreateTemplate<::T, __VA_ARGS__>(#T)
