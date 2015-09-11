// Resource.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <sys/stat.h>
#include "../include/Resource/Resource.h"
#include "../include/Resource/Asset.h"

///////////////////
///   Statics   ///

Table<String, Resource*> resourceTable;

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Resource)
.Property("Path", &Resource::_path, nullptr, "The path to the Resource.")
.Property("Size", &Resource::_size, nullptr, "The size of the Resource.");

////////////////////////
///   Constructors   ///

Resource::Resource(const Path& path)
	: _path(path)
{
	resourceTable[path] = this;

	struct stat fileStats;

	if (stat(path.ToString().Cstr(), &fileStats) == -1)
	{
		Console::Warning("Resource '@' could not be found.", path);
		return;
	}

	_size = uint32(fileStats.st_size);
}

Resource::~Resource()
{
	resourceTable[_path] = nullptr;
}
