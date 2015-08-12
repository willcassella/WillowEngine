// Asset.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"
#include "Reflection/AssetInfo.h"

/////////////////
///   Types   ///

class RESOURCE_API Asset : public Object
{
	///////////////////////
	///   Information   ///
public:

	EXTENDS(Object);

	//////////////////////
	///   Reflection   ///
public:

	static const ClassInfo StaticTypeInfo;
	const AssetInfo& GetType() const override = 0;
};
