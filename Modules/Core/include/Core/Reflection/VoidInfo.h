// VoidInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "PrimitiveInfo.h"

/////////////////
///   Types   ///

class CORE_API VoidInfo final : public TypeInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(TypeInfo);
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