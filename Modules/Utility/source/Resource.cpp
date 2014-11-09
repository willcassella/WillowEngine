// Resource.cpp

#include "..\include\Utility\Table.h"
#include "..\include\Utility\Resource.h"
using namespace Willow;

static Table<String, Resource*> LoadedResources;

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