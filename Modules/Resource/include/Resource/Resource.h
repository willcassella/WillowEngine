// Resource.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"
#include "Forwards/Resource.h"
#include "Path.h"

class RESOURCE_API Resource : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Object)
	friend Asset;

	////////////////////////
	///   Constructors   ///
public:

	Resource(Path path);

	///////////////////
	///   Methods   ///
public:

	/** Returns the path to this this Resource. */
	FORCEINLINE const Path& GetPath() const
	{
		return _path;
	}

	/** Returns the size of this Resource on disk. */
	FORCEINLINE uint32 GetSize() const
	{
		return _size;
	}

	////////////////
	///   Data   ///
private:

	Path _path;
	uint32 _size;
};
