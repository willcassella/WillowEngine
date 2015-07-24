// PrimitiveInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "TypeInfo.h"

/** This is the base of all types that are intrinsic to the language */
class CORE_API PrimitiveInfo : public TypeInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(TypeInfo);

	////////////////////////
	///   Constructors   ///
public:

	// @TODO: Documentation
	template <typename PrimitiveT>
	static PrimitiveInfo Create(CString name)
	{
		PrimitiveT* dummy = nullptr;
		return PrimitiveInfo(dummy, name);
	}

protected:

	// @TODO: Documentation
	template <typename PrimitiveT>
	PrimitiveInfo(PrimitiveT* dummy, CString name)
		: Super(dummy, name)
	{
		static_assert(stdEXT::is_primitive<PrimitiveT>::value || std::is_fundamental<PrimitiveT>::value,
			"Primitives types must be primitive");
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this type is castable (via reinterpret_cast) to the given type */
	bool IsCastableTo(const TypeInfo& type) const override;
};