// Resource.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"

class RESOURCE_API Resource : public Object
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
	Resource(const String& path);
	Resource(const Resource& copy) = delete;
	Resource(Resource&& other) = delete;
	~Resource() override;

	///////////////////
	///   Methods   ///
public:

	String GetPath() const;
		
private:

	static Resource* FindLoadedResource(const String& path);

	/////////////////////
	///   Operators   ///
public:

	Resource& operator=(const Resource& copy) = delete;
	Resource& operator=(Resource&& other) = delete;

	////////////////
	///   Data   ///
private:

	String _path;
	uint32 _refs;
};