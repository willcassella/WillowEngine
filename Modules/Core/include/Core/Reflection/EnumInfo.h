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

	////////////////////////
	///   Constructors   ///
public:

	template <typename EnumT>
	static EnumInfo Create(const String& name)
	{
		EnumT* dummy = nullptr;
		return EnumInfo(dummy, name);
	}

private:

	template <typename EnumT>
	EnumInfo(EnumT* dummy, const String& name)
		: Super(dummy, name)
	{
		static_assert(std::is_enum<EnumT>::value, "The type given to 'EnumInfo::Create()' must be an enum type.");

		_underlyingType = &TypeOf<std::underlying_type_t<EnumT>>();
	}

	///////////////////
	///   Methods   ///
public:

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