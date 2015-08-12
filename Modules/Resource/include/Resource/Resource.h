// Resource.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"
#include "Forwards/Resource.h"
#include "Reflection/ResourceInfo.h"
#include "Path.h"

class RESOURCE_API Resource : public Object
{
	///////////////////////
	///   Information   ///
public:

	EXTENDS(Object);
	friend Asset;

	//////////////////////
	///   Reflection   ///
public:

	static const ClassInfo StaticTypeInfo;
	const ResourceInfo& GetType() const override = 0;

	////////////////////////
	///   Constructors   ///
public:

	Resource(const Path& path);
	~Resource() override;

	///////////////////
	///   Methods   ///
public:

	/** Returns the path to this this Resource. */
	FORCEINLINE const Path& GetPath() const
	{
		return _path;
	}

	FORCEINLINE uint32 GetSize()
	{
		return _size;
	}

	////////////////
	///   Data   ///
private:

	Path _path;
	uint32 _size;
};
