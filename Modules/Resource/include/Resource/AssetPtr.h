// ResourcePtr.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Asset.h"
#include "AssetManager.h"

/////////////////
///   Types   ///

template <class AssetT>
struct AssetPtr final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	////////////////////////
	///   Constructors   ///
public:

	AssetPtr()
		: _asset(nullptr)
	{
		// All done
	}
	AssetPtr(const Path& path)
	{
		_asset = AssetManager::FindAsset<AssetT>(path);
	}

	/////////////////////
	///   Operators   ///
public:

	const AssetT& operator*() const
	{
		return *_asset;
	}
	const AssetT* operator->() const
	{
		return _asset;
	}
	bool operator==(std::nullptr_t)
	{
		return _asset == nullptr;
	}
	bool operator!=(std::nullptr_t)
	{
		return _asset != nullptr;
	}
	operator bool() const
	{
		return _asset != nullptr;
	}
	AssetPtr& operator=(const Path& path)
	{
		_asset = AssetManager::FindAsset<AssetT>(path);
		return self;
	}
	
	////////////////
	///   Data   ///
private:

	const AssetT* _asset;
};

//////////////////////
///   Reflection   ///

template <class AssetT>
BUILD_TEMPLATE_REFLECTION(AssetPtr, AssetT);
