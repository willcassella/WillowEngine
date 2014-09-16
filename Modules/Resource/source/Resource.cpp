// Resource.cpp

#include <map>
#include "..\include\Resource\Resource.h"
using namespace Willow;

static std::map<String, Resource*> LoadedResources;

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
	if (LoadedResources.find(path) == LoadedResources.end())
	{
		return nullptr;
	}
	else
	{
		return LoadedResources[path];
	}
}