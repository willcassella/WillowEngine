// Resource.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Reflection/ClassInfo.h>
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
	FORCEINLINE std::size_t GetSize() const
	{
		return _size;
	}

	////////////////
	///   Data   ///
private:

	Path _path;
	std::size_t _size;
};
