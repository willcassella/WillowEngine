// Asset.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Path.h"
#include "Reflection/AssetInfo.h"

/////////////////
///   Types   ///

class RESOURCE_API Asset : public Object
{
	///////////////////////
	///   Information   ///
public:

	EXTENDS(Object)

	//////////////////////
	///   Reflection   ///
public:

	REFLECTION_DECL(ClassInfo)
	const AssetInfo& GetType() const override = 0;

	////////////////////////
	///   Constructors   ///
public:

	Asset(const Path& path);

	///////////////////
	///   Methods   ///
public:

	FORCEINLINE const Path& GetPath() const
	{
		return _path;
	}

	////////////////
	///   Data   ///
private:

	Path _path;
};
