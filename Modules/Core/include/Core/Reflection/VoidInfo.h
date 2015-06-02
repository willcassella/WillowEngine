// VoidInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "PrimitiveInfo.h"

/////////////////
///   Types   ///

class CORE_API VoidInfo final : public PrimitiveInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(PrimitiveInfo);
	friend Implementation::TypeOf<void>;

	////////////////////////
	///   Constructors   ///
private:

	VoidInfo();

	///////////////////
	///   Methods   ///
public:

	bool IsCastableTo(const TypeInfo& type) const override;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** TypeOf for 'void' */
	template <>
	struct TypeOf < void >
	{
		/** Defined in 'VoidInfo.cpp' */
		static const VoidInfo StaticTypeInfo;

		FORCEINLINE static const VoidInfo& Function()
		{
			return StaticTypeInfo;
		}

		/** It is not possible to retrieve type data for an instance of 'void', so that Function is not necessary */
	};
}