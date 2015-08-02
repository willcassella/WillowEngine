// Asset.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"
#include "Reflection/AssetInfo.h"

class RESOURCE_API Asset : public Object
{
	///////////////////////
	///   Information   ///
public:

	EXTENDS(Object)

	//////////////////////
	///   Reflection   ///
public:

	static const ClassInfo StaticTypeInfo;
	const AssetInfo& GetType() const override = 0;

	////////////////////////
	///   Constructors   ///
public:

	Asset(const Resource& resource);
	Asset(const Asset& copy) = delete;
	Asset(Asset&& move) = delete;
	~Asset();

	///////////////////
	///   Methods   ///
public:

	/** Returns a reference to the Resource that this Asset uses. */
	FORCEINLINE const Resource& GetResource() const
	{
		return *_resource;
	}

	/** Called when the Resource is reloaded. */
	virtual void OnReload() = 0;

	/////////////////////
	///   Operators   ///
public:

	Asset& operator=(const Asset& copy) = delete;
	Asset& operator=(Asset&& move) = delete;

	////////////////
	///   Data   ///
private:

	const Resource* _resource;
	mutable uint32 _refs;
};
