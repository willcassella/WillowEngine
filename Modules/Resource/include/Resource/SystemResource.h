// SystemResource.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"

class RESOURCE_API SystemResource : public Object
{
	///////////////////////
	///   Information   ///
public:
		
	REFLECTABLE_CLASS;
	EXTENDS(Object);
	template <class T> friend class ResourceHandle;

	////////////////////////
	///   Constructors   ///
public:

	/** Loads a resource from the given file path */
	SystemResource(const String& path);
	SystemResource(const SystemResource& copy) = delete;
	SystemResource(SystemResource&& other) = delete;
	~SystemResource() override;

	///////////////////
	///   Methods   ///
public:

	String GetPath() const;
		
private:

	static SystemResource* FindLoadedResource(const String& path);

	/////////////////////
	///   Operators   ///
public:

	SystemResource& operator=(const SystemResource& copy) = delete;
	SystemResource& operator=(SystemResource&& other) = delete;

	////////////////
	///   Data   ///
private:

	String _path;
	uint32 _refs;
};