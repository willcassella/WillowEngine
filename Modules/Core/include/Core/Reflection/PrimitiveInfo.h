// PrimitiveInfo.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "TypeInfo.h"

/////////////////
///   Types   ///

/** This is the base of all types that are intrinsic to the language */
class CORE_API PrimitiveInfo : public TypeInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(TypeInfo)

	////////////////////////
	///   Constructors   ///
public:

	// @TODO: Documentation
	template <typename PrimitiveT>
	PrimitiveInfo(const TypeInfoBuilder<PrimitiveT, PrimitiveInfo>& builder)
		: Base(builder)
	{
		static_assert(stde::is_primitive<PrimitiveT>::value || std::is_fundamental<PrimitiveT>::value || std::is_enum<PrimitiveT>::value,
			"Primitives types must be primitive");
	}

	///////////////////
	///   Methods   ///
public:

	bool is_castable_to(const TypeInfo& type) const override;

	bool is_stable() const final override;
};

/** Generic TypeInfoBuilder for PrimitiveInfo */
template <typename PrimitiveT>
struct TypeInfoBuilder < PrimitiveT, PrimitiveInfo > : TypeInfoBuilderBase<PrimitiveT, PrimitiveInfo>
{
	////////////////////////
	///   Constructors   ///
public:

	// TODO: Documentation
	TypeInfoBuilder(CString name)
		: TypeInfoBuilderBase<PrimitiveT, PrimitiveInfo>(name)
	{
		// All done
	}
};
