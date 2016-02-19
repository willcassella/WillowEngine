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

	///////////////////
	///   Methods   ///
public:

	String ToString() const
	{
		if (_asset)
		{
			return _asset->GetPath();
		}
		else
		{
			return "null";
		}
	}

	void ToArchive(ArchiveWriter& writer) const
	{
		if (_asset)
		{
			writer.SetValue(_asset->GetPath());
		}
		else
		{
			writer.SetValue("null"_s);
		}
	}

	void FromArchive(const ArchiveReader& reader)
	{
		String path;
		reader.GetValue(path);

		if (path == "null")
		{
			_asset = nullptr;
		}
		else
		{
			_asset = AssetManager::FindAsset<AssetT>(path);
		}
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
		return *this;
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
