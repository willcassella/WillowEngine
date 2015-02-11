// Resource.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Resource/Resource.h"

static Table<String, Resource*> LoadedResources;

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Resource);

////////////////////////
///   Constructors   ///

Resource::Resource(const String& path)
	: _path(path), _refs(0)
{
	LoadedResources[path] = this;
}

Resource::~Resource()
{
	LoadedResources[_path] = nullptr;
}

///////////////////
///   Methods   ///

String Resource::GetPath() const
{
	return _path;
}

Resource* Resource::FindLoadedResource(const String& path)
{
	if (!LoadedResources.HasKey(path))
	{
		return nullptr;
	}
	else
	{
		return LoadedResources[path];
	}
}