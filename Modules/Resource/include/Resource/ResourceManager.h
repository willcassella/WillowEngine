// ResourceManager.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Containers/Table.h>
#include "Resource.h"

struct RESOURCE_API ResourceManager final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	////////////////////////
	///   Constructors   ///
private:

	ResourceManager() = default;
	ResourceManager(const ResourceManager& copy) = delete;
	ResourceManager(ResourceManager&& move) = delete;

	///////////////////
	///   Methods   ///
public:

	// TODO: Documentation
	template <class ResourceT>
	static const ResourceT* FindResource(const String& path)
	{
		// Search for the resource
		if (auto ppReource = Instance()._resourceTable.Find(path))
		{
			// We found the resource, but is it of the type we want?
			if (auto pResource = Cast<ResourceT>(**ppReource))
			{
				return pResource;
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			Instance()._resourceTable[path] = New<ResourceT>(path);
		}
	}

private:

	static ResourceManager& Instance();

	/////////////////////
	///   Operators   ///
public:

	ResourceManager& operator=(const ResourceManager& copy) = delete;
	ResourceManager& operator=(ResourceManager&& move) = delete;

	////////////////
	///   Data   ///
private:

	Table<String, OwnerPtr<Resource>> _resourceTable;
};
