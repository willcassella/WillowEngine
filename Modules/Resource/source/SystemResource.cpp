// SystemResource.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Resource/SystemResource.h"

static Table<String, SystemResource*> LoadedResources;

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(SystemResource);

////////////////////////
///   Constructors   ///

SystemResource::SystemResource(const String& path)
	: _path(path), _refs(0)
{
	LoadedResources[path] = this;
}

SystemResource::~SystemResource()
{
	LoadedResources[_path] = nullptr;
}

///////////////////
///   Methods   ///

String SystemResource::GetPath() const
{
	return _path;
}

SystemResource* SystemResource::FindLoadedResource(const String& path)
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