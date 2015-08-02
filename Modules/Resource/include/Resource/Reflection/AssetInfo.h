// AssetInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"
#include "../Forwards/Resource.h"
#include "../Forwards/Reflection.h"

class RESOURCE_API AssetInfo final : public ClassInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(ClassInfo)

	template <typename T, class TypeInfoT>
	friend struct TypeInfoBuilder;

	///////////////////////
	///   Inner Types   ///
public:

	typedef void(*AssetConstructor)(byte*, const Resource&);

	////////////////////////
	///   Constructors   ///
public:

	// TODO: Documentation
	template <class AssetT>
	AssetInfo(const TypeInfoBuilder<AssetT, AssetInfo>& builder)
		: Base(builder)
	{
		// TODO
	}

	////////////////
	///   Data   ///
private:

	struct Data
	{
		Table<const ResourceInfo*, AssetConstructor> Constructors;
	} _data;
};

/** Generic TypeInfoBuilder for AssetInfo */
template <class AssetT>
struct TypeInfoBuilder < AssetT, AssetInfo > : TypeInfoBuilderBase<AssetT, AssetInfo>
{
	///////////////////////
	///   Information   ///
public:

	friend AssetInfo;

	////////////////////////
	///   Constructors   ///
public:

	// TODO: Documentation
	TypeInfoBuilder(CString name)
		: TypeInfoBuilderBase<AssetT, AssetInfo>(name)
	{
		// All done
	}

	////////////////
	///   Data   ///
private:

	mutable AssetInfo::Data _data;
};

//////////////////
///   Macros   ///

// TODO: Documentation
#define REFLECTABLE_ASSET							\
public:												\
	static const ::AssetInfo StaticTypeInfo;		\
	const ::AssetInfo& GetType() const override		\
	{												\
		return StaticTypeInfo;						\
	}
