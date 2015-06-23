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
	template <typename AnyPrimitiveType>
	static PrimitiveInfo Create(const String& name)
	{
		AnyPrimitiveType* dummy = nullptr;
		return PrimitiveInfo(dummy, name);
	}

protected:

	template <typename AnyPrimitiveType>
	PrimitiveInfo(AnyPrimitiveType* dummy, const String& name)
		: Super(dummy, name)
	{
		static_assert(std::is_arithmetic<AnyPrimitiveType>::value || 
			std::is_pointer<AnyPrimitiveType>::value ||
			std::is_fundamental<AnyPrimitiveType>::value,
			"Primitives types must be primitive");
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this type is castable (via reinterpret_cast) to the given type */
	bool IsCastableTo(const TypeInfo& type) const override;
};