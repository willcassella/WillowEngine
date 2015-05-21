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
public:

	VoidInfo(VoidInfo&& move) = default; // @TODO: See if this can be removed

private:

	VoidInfo();

	///////////////////
	///   Methods   ///
public:

	bool IsCastableTo(const TypeInfo& type) const override;

	/////////////////////
	///   Operators   ///
public:

	TypeInfo& operator=(const TypeInfo& copy) = delete;
	TypeInfo& operator=(TypeInfo&& move) = delete;
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

		FORCEINLINE static const TypeInfo& Function()
		{
			return StaticTypeInfo;
		}

		/** It is not possible to retrieve type data for an instance of 'void', so that Function is not necessary */
	};
}