// Asset.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Resource/Asset.h"

///////////////////
///   Statics   ///

std::atomic<AssetID> _lastID(0);

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Asset);

////////////////////////
///   Constructors   ///

Asset::Asset(const Path& path)
	: _path(path)
{
	_id = ++_lastID;
}
