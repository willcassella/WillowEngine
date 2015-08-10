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

	////////////////////////
	///   Constructors   ///
public:

	// TODO: Documentation
	template <typename EnumT>
	static EnumInfo Create(CString name)
	{
		EnumT* dummy = nullptr;
		return EnumInfo(dummy, name);
	}

private:

	// TODO: Documentation
	template <typename EnumT>
	EnumInfo(EnumT* dummy, CString name)
		: Base(dummy, name)
	{
		static_assert(std::is_enum<EnumT>::value, "The type given to 'EnumInfo::Create()' must be an enum type.");

		_underlyingType = &TypeOf<std::underlying_type_t<EnumT>>();
	}

	///////////////////
	///   Methods   ///
public:

	bool IsCastableTo(const TypeInfo& type) const override;

	/** Returns the underlying type of this enum */
	FORCEINLINE const PrimitiveInfo& GetUnderlyingType() const
	{
		return *_underlyingType;
	}

	////////////////
	///   Data   ///
private:

	const PrimitiveInfo* _underlyingType;
};

//////////////////
///   Macros   ///

// TODO: Documentation
#define ENUM_REFLECTION(E) const ::EnumInfo Implementation::TypeOf<E>::StaticTypeInfo = ::EnumInfo::Create<E>(#E) 
