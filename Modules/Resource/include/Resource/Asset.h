// Asset.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Path.h"

/////////////////
///   Types   ///

/** Uniquely identifies each asset. */
using AssetID = uint32;

class RESOURCE_API Asset : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Object)

	////////////////////////
	///   Constructors   ///
public:

	Asset(const Path& path);

	///////////////////
	///   Methods   ///
public:

	/** Returns the path for this Asset. */
	FORCEINLINE const Path& GetPath() const
	{
		return _path;
	}

	/** Returns the Unique ID for this asset. */
	FORCEINLINE AssetID GetID() const
	{
		return _id;
	}

	////////////////
	///   Data   ///
private:

	Path _path;
	AssetID _id;
};
