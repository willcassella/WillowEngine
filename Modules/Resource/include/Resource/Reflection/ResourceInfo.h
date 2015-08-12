// ResourceInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"
#include "../Forwards/Resource.h"
#include "../Path.h"

/////////////////
///   Types   ///

class RESOURCE_API ResourceInfo final : public ClassInfo
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

	/** Function signature for constructing resources. */
	typedef void(*ResourceConstructor)(byte*, const Path&);

	////////////////////////
	///   Constructors   ///
public:

	// TODO: Documentation
	template <class ResourceT>
	ResourceInfo(const TypeInfoBuilder<ResourceT, ResourceInfo>& builder)
		: Base(builder), _data(std::move(builder._data))
	{
		static_assert(std::is_base_of<Resource, ResourceT>::value, "The given type must be a Resource type.");
		static_assert(std::is_constructible<ResourceT, const Path&>::value, "Resources must be constructible with paths.");
	}

	////////////////
	///   Data   ///
private:

	struct Data
	{
		ResourceConstructor constructor;
	} _data;
};

/** Generic TypeInfoBuilder for ResourceInfo */
template <class ResourceT>
struct TypeInfoBuilder < ResourceT, ResourceInfo > : TypeInfoBuilderBase<ResourceT, ResourceInfo>
{
	///////////////////////
	///   Information   ///
public:

	friend ResourceInfo;

	////////////////////////
	///   Constructors   ///
public:

	// TODO: Documentation
	TypeInfoBuilder(CString name)
		: TypeInfoBuilderBase<ResourceT, ResourceInfo>(name)
	{
		_data.constructor = Implementation::Construct<ResourceT, const Path&>::Function;
	}

	////////////////
	///   Data   ///
private:

	mutable ResourceInfo::Data _data;
};

//////////////////
///   Macros   ///

// TODO: Documentation
#define REFLECTABLE_RESOURCE						\
public:												\
	static const ::ResourceInfo StaticTypeInfo;		\
	const ::ResourceInfo& GetType() const override	\
	{												\
		return StaticTypeInfo;						\
	}
