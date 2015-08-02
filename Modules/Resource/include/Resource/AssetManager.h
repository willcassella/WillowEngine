// AssetManager.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Containers/Table.h>
#include "Asset.h"

struct RESOURCE_API AssetManager final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT
	template <class AssetT>
	friend struct AssetPtr;

	////////////////////////
	///   Constructors   ///
private:

	AssetManager() = default;
	AssetManager(const AssetManager& copy) = delete;
	AssetManager(AssetManager&& move) = delete;

	///////////////////
	///   Methods   ///
private:

	// TODO: Documentation
	template <class AssetT>
	static const AssetT* FindAsset(const String& resource)
	{
		// Search for the asset
		if (auto ppAsset = Instance()._assetTable.Find(resource))
		{

		}
		else
		{
			// Try to create a new asset
			if (auto pResource = ResourceManager::F)
		}
	}

	static AssetManager& Instance();

	/////////////////////
	///   Operators   ///
public:

	AssetManager& operator=(const AssetManager& copy) = delete;
	AssetManager& operator=(AssetManager&& move) = delete;

	////////////////
	///   Data   ///
private:

	Table<String, OwnerPtr<Asset>> _assetTable;
};
