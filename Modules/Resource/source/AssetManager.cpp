// AssetManager.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Resource/AssetManager.h"

///////////////////
///   Methods   ///

AssetManager& AssetManager::Instance()
{
	static AssetManager instance;
	return instance;
}
