// Asset.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Resource/Asset.h"
#include "../include/Resource/Resource.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Asset);

////////////////////////
///   Constructors   ///

Asset::Asset(const Resource& resource)
	: _resource(&resource)
{
	_resource->_assets.Add(this);
}

Asset::~Asset()
{
	_resource->_assets.DeleteAll(this);
}
