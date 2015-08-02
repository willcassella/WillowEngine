// StructInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Containers/Array.h"
#include "../Containers/List.h"
#include "../Containers/Queue.h"
#include "../Containers/Stack.h"
#include "../Containers/Table.h"
#include "../Containers/Pair.h"
#include "CompoundInfo.h"

/////////////////
///   Types   ///

/** Type information for structs */
class CORE_API StructInfo : public CompoundInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(CompoundInfo)

	////////////////////////
	///   Constructors   ///
public:

	// @TODO: Documentation
	template <class StructT>
	StructInfo(TypeInfoBuilder<StructT, StructInfo>& builder)
		: Base(builder)
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this type is castable (via 'reinterpret_cast') to the given type */
	bool IsCastableTo(const TypeInfo& type) const override;
};

/** Generic TypeInfoBuilder for StructInfo */
template <class StructT>
struct TypeInfoBuilder < StructT, StructInfo > : TypeInfoBuilderBase<StructT, StructInfo>
{
	///////////////////////
	///   Information   ///
public:

	friend StructInfo;

	////////////////////////
	///   Constructors   ///
public:

	TypeInfoBuilder(CString name)
		: TypeInfoBuilderBase<StructT, StructInfo>(name)
	{
		static_assert(!std::is_polymorphic<StructT>::value, "Structs may not be polymorphic");
	}
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	///** Register TypeInfo for std::intializer_list */
	//template <typename T>
	//const StructInfo GetType<std::initializer_list<T>>::StaticTypeInfo =
	//	StructInfo::CreateTemplate<std::initializer_list, T>("std::initializer_list");

	/** Register TypeInfo for 'Array' */
	template <typename T>
	const StructInfo TypeOf<Array<T>>::StaticTypeInfo =
		TypeInfoBuilder<Array<T>>("Array");

	///** Register TypeInfo for List */
	//template <typename T>
	//const StructInfo TypeOf<List<T>>::StaticTypeInfo = 
	//	StructInfo::CreateTemplate<List, T>("List");

	///** Register TypeInfo for Queue */
	//template <typename T>
	//const StructInfo TypeOf<Queue<T>>::StaticTypeInfo =
	//	StructInfo::CreateTemplate<Queue, T>("Queue");

	///** Register TypeInfo for Stack */
	//template <typename T>
	//const StructInfo TypeOf<Stack<T>>::StaticTypeInfo = 
	//	StructInfo::CreateTemplate<Stack, T>("Stack");

	///** Register TypeInfo for Table */
	//template <typename KeyT, typename ValueT>
	//const StructInfo TypeOf<Table<KeyT, ValueT>>::StaticTypeInfo = 
	//	StructInfo::CreateTemplate<Table, KeyT, ValueT>("Table");

	///** Register TypeInfo for Pair */
	//template <typename A, typename B>
	//const StructInfo TypeOf<Pair<A, B>>::StaticTypeInfo = 
	//	StructInfo::CreateTemplate<Pair, A, B>("Pair");
}
