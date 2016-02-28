// EnumInfo.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Containers/Union.h"
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

	///////////////////////
	///   Inner Types   ///
public:

	/** Union of all possible underlying enum types. */
	using GenericEnum = Union<byte, int16, uint16, int32, uint32, int64, uint64>;

	/** Data held by each entry in this Enum's table of values (value, description). */
	using ValueEntry = Pair<GenericEnum, CString>;

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
		return _data.IsBitFlag;
	}

	/** Returns the underlying type of this enum */
	FORCEINLINE const PrimitiveInfo& GetUnderlyingType() const
	{
		return *_data.UnderlyingType;
	}

	/** Returns all the values for this enum. */
	FORCEINLINE const Table<String, ValueEntry>& GetValues() const
	{
		return _data.Values;
	}

	////////////////
	///   Data   ///
private:

	const struct Data
	{
		const PrimitiveInfo* UnderlyingType;
		Table<String, ValueEntry> Values;
		bool IsBitFlag = false;
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

	/////////////////////
	///   Constants   ///
private:

	/** Default description for enum value. */
	static constexpr CString DefaultDescription = "";

	////////////////////////
	///   Constructors   ///
public:

	TypeInfoBuilder(CString name)
		: TypeInfoBuilderBase<EnumT, EnumInfo>(name)
	{
		_data.UnderlyingType = &TypeOf<std::underlying_type_t<EnumT>>();
	}

	///////////////////
	///   Methods   ///
public:

	/** Indicates that this enum represents a bit flag. */
	auto& IsBitFlag()
	{
		_data.IsBitFlag = true;
		return this->AsMostSpecificTypeInfoBuilder();
	}

	/** Adds a value for this enum, with a default description. */
	auto& Value(CString name, EnumT value)
	{
		return this->Value(name, value, DefaultDescription);
	}

	/** Adds a value for this enum. */
	auto& Value(CString name, EnumT value, CString description)
	{
		_data.Values.Insert(name, EnumInfo::ValueEntry{ static_cast<std::underlying_type_t<EnumT>>(value), description });
		return this->AsMostSpecificTypeInfoBuilder();
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
