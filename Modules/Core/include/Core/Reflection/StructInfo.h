// StructInfo.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Containers/Array.h"
#include "../Containers/List.h"
#include "../Containers/Queue.h"
#include "../Containers/Stack.h"
#include "../Containers/Table.h"
#include "../Containers/Pair.h"
#include "CompoundInfo.h"
#include "TypePtr.h"

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

	template <typename T, class TypeInfoT>
	friend struct TypeInfoBuilder;

	////////////////////////
	///   Constructors   ///
public:

	// @TODO: Documentation
	template <class StructT>
	StructInfo(const TypeInfoBuilder<StructT, StructInfo>& builder)
		: Base(builder), _data(std::move(builder._data))
	{
		static_assert(!std::is_polymorphic<StructT>::value, "Structs may not be polymorphic");
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this type is castable (via 'reinterpret_cast') to the given type */
	bool IsCastableTo(const TypeInfo& type) const override;

	/** Returns whether this struct is stable (its memory layout is unlikely to ever change). */
	bool IsStable() const final override;

	////////////////
	///   Data   ///
private:

	struct Data
	{
		bool isStable = false;
	} _data;
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
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	// TODO: Documentation
	const auto& IsStable()
	{
		_data.isStable = true;
		return this->SelfAsMostSpecificTypeInfoBuilder();
	}

	////////////////
	///   Data   ///
private:

	mutable StructInfo::Data _data;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Register TypeInfo for std::intializer_list */
	template <typename T>
	const StructInfo TypeOf<std::initializer_list<T>>::StaticTypeInfo =
		TypeInfoBuilder<std::initializer_list<T>>("std::initializer_list");

	/** Register TypeInfo for 'Array' */
	template <typename T>
	const StructInfo TypeOf<Array<T>>::StaticTypeInfo =
		TypeInfoBuilder<Array<T>>("Array");

	/** Register TypeInfo for List */
	template <typename T>
	const StructInfo TypeOf<List<T>>::StaticTypeInfo =
		TypeInfoBuilder<List<T>>("List");

	/** Register TypeInfo for Queue */
	template <typename T>
	const StructInfo TypeOf<Queue<T>>::StaticTypeInfo =
		TypeInfoBuilder<Queue<T>>("Queue");

	/** Register TypeInfo for Stack */
	template <typename T>
	const StructInfo TypeOf<Stack<T>>::StaticTypeInfo =
		TypeInfoBuilder<Stack<T>>("Stack");

	/** Register TypeInfo for Table */
	template <typename KeyT, typename ValueT>
	const StructInfo TypeOf<Table<KeyT, ValueT>>::StaticTypeInfo =
		TypeInfoBuilder<Table<KeyT, ValueT>>("Table");

	/** Register TypeInfo for Pair */
	template <typename A, typename B>
	const StructInfo TypeOf<Pair<A, B>>::StaticTypeInfo =
		TypeInfoBuilder<Pair<A, B>>("Pair");
}

//////////////////////
///   Reflection   ///

template <class TypeInfoT>
BUILD_TEMPLATE_REFLECTION(TypePtr, TypeInfoT);
