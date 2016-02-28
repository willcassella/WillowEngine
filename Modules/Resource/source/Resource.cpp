// Resource.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <sys/stat.h>
#include "../include/Resource/Resource.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::Resource)
.Data("Path", &Resource::_path)
.Data("Size", &Resource::_size)
.Property("Path", &Resource::GetPath, nullptr, "The path to the Resource.")
.Property("Size", &Resource::GetSize, nullptr, "The size of the Resource.");

namespace Willow
{
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

		_size = static_cast<std::size_t>(fileStats.st_size);
	}
}
