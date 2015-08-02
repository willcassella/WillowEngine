// ResourcePtr.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Asset.h"
#include "Resource.h"

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
	//ResourcePtr(const String& path)
	//{
	//	_resource = Resource
	//}

	////////////////
	///   Data   ///
private:

	AssetT* _asset;
};

//////////////////////
///   Reflection   ///

template <class AssetT>
STRUCT_REFLECTION(AssetPtr<AssetT>);
