// Resource.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <sys/stat.h>
#include "../include/Resource/Resource.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Resource)
.Property("Path", &Resource::_path, nullptr, "The path to the Resource.")
.Property("Size", &Resource::_size, nullptr, "The size of the Resource.");

////////////////////////
///   Constructors   ///

Resource::Resource(Path path)
	: _path(std::move(path))
{
	struct stat fileStats;

	if (stat(_path.ToString().Cstr(), &fileStats) == -1)
	{
		Console::Warning("Resource '@' could not be found.", _path);
		return;
	}

	_size = uint32(fileStats.st_size);
}
