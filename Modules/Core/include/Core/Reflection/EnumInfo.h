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

	REFLECTABLE_CLASS
	EXTENDS(PrimitiveInfo)

	template <typename T, class TypeInfoT>
	friend struct TypeInfoBuilder;

	////////////////////////
	///   Constructors   ///
public:

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

	/** Returns whether this enum represents a bit flag. */
	FORCEINLINE bool IsBitFlag() const
	{
		return _data.isBitFlag;
	}

	/** Returns the underlying type of this enum */
	FORCEINLINE const PrimitiveInfo& GetUnderlyingType() const
	{
		return *_data.underlyingType;
	}

	/** Returns all the values for this enum. */
	FORCEINLINE const Table<String, int64>& GetValues() const
	{
		return _data.values;
	}

	////////////////
	///   Data   ///
private:

	struct Data
	{
		const PrimitiveInfo* underlyingType;
		Table<String, int64> values;
		bool isBitFlag = false;
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

	TypeInfoBuilder(CString name)
		: TypeInfoBuilderBase<EnumT, EnumInfo>(name)
	{
		_data.underlyingType = &TypeOf<std::underlying_type_t<EnumT>>();
	}

	///////////////////
	///   Methods   ///
public:

	/** Indicates that this enum represents a bit flag. */
	auto& IsBitFlag()
	{
		_data.isBitFlag = true;
		return this->SelfAsMostSpecificTypeInfoBuilder();
	}

	/** Adds a value for this enum. */
	auto& Value(CString name, EnumT value, CString /*description*/ = "")
	{
		_data.values[name] = static_cast<int64>(value);
		return this->SelfAsMostSpecificTypeInfoBuilder();
	}

	////////////////
	///   Data   ///
private:

	mutable EnumInfo::Data _data;
};

//////////////////
///   Macros   ///

// TODO: Documentation
#define BUILD_ENUM_REFLECTION(E) const ::EnumInfo Implementation::TypeOf<E>::StaticTypeInfo = ::TypeInfoBuilder<E>(#E) 
