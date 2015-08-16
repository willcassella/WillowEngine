// EnumInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "PrimitiveInfo.h"

/////////////////
///   Types   ///

class CORE_API EnumInfo final : public PrimitiveInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(PrimitiveInfo);

	template <typename T, class TypeInfoT>
	friend struct TypeInfoBuilder;

	////////////////////////
	///   Constructors   ///
public:

	// TODO: Documentation
	template <typename EnumT>
	EnumInfo(const TypeInfoBuilder<EnumT, EnumInfo>& builder)
		: Base(builder), _data(std::move(builder._data))
	{
		static_assert(std::is_enum<EnumT>::value, "The type given to 'EnumInfo::Create()' must be an enum type.");
	}

	///////////////////
	///   Methods   ///
public:

	bool IsCastableTo(const TypeInfo& type) const override;

	/** Returns the underlying type of this enum */
	FORCEINLINE const PrimitiveInfo& GetUnderlyingType() const
	{
		return *_data.underlyingType;
	}

	////////////////
	///   Data   ///
private:

	struct Data
	{
		const PrimitiveInfo* underlyingType;
	} _data;
};

// TODO: Documentation
template <typename EnumT>
struct TypeInfoBuilder< EnumT, EnumInfo > final : TypeInfoBuilderBase<EnumT, EnumInfo>
{
	///////////////////////
	///   Information   ///
public:

	friend EnumInfo;

	////////////////////////
	///   Constructors   ///
public:

	// TODO: Documentatnion
	TypeInfoBuilder(CString name)
		: TypeInfoBuilderBase<EnumT, EnumInfo>(name)
	{
		_data.underlyingType = &TypeOf<std::underlying_type_t<EnumT>>();
	}

	////////////////
	///   Data   ///
private:

	mutable EnumInfo::Data _data;
};

//////////////////
///   Macros   ///

// TODO: Documentation
#define ENUM_REFLECTION(E) const ::EnumInfo Implementation::TypeOf<E>::StaticTypeInfo = ::TypeInfoBuilder<E>(#E) 
