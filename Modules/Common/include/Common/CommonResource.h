// SystemResource.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Resource/ResourcePtr.h>
#include <Core/Resource/Resource.h>
#include "config.h"

class COMMON_API CommonResource : public Resource
{
	///////////////////////
	///   Information   ///
public:
		
	REFLECTABLE_CLASS;
	EXTENDS(Object);
	template <class T> friend struct ResourcePtr;

	////////////////////////
	///   Constructors   ///
public:

	/** Loads a resource from the given file path */
	CommonResource(const String& path);
	~CommonResource() override;
		
private:

	static CommonResource* FindLoadedResource(const String& path);
};