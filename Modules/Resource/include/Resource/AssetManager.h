// AssetManager.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Containers/Table.h>
#include "Path.h"
#include "Asset.h"

/** Possible urgencies for an asset to be loaded. */
enum class AssetLoadMode : byte
{
	None,		// The asset is not required at this time.
	Delayed,	// The asset will be needed, but not for the forseeable future.
	Normal,		// The asset is needed in the near future.
	Immediate	// The asset is needed immediately.
};

enum class AssetStatus : byte
{
	NotLoaded,	// The asset has not been loaded.
	Loading,	// The asset is currently being loaded.
	Loaded,		// The asset has been loaded.
};

/** Information for a requested asset. */
struct RESOURCE_API RequestedAsset final
{
	////////////////////////
	///   Constructors   ///
public:

	RequestedAsset();

	//////////////////
	///   Fields   ///
public:

	/** The requested asset (null until loaded). */
	UniquePtr<class Asset> Asset;

	/** The maximum requested urgency of loading the asset.  */
	AssetLoadMode LoadMode = AssetLoadMode::None;

	/** The status of the asset. */
	AssetStatus Status = AssetStatus::NotLoaded;
	
	/** The total number of references to this asset. */
	uint32 Refs = 0;
};

/** Singleton responsible for loading and unloading assets as they are needed. */
struct RESOURCE_API AssetManager final
{
	///////////////////////
	///   Information   ///
public:

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
	static const AssetT* FindAsset(const Path& path)
	{
		// Search for the asset
		if (auto ppAsset = Instance()._requestedAssets.Find(path))
		{
			return Cast<AssetT>(**ppAsset);
		}
		else
		{
			// Create a new asset
			UniquePtr<AssetT> asset = New<AssetT>(path);
			auto pAsset = asset.Get();

			// Add it to the table
			Instance()._requestedAssets[path] = asset.Transfer();

			return pAsset;
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

	Table<Path, UniquePtr<Asset>> _requestedAssets;
};
