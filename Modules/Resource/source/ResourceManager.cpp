// ResourceManager.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Resource/ResourceManager.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(ResourceManager);

///////////////////
///   Methods   ///

ResourceManager& ResourceManager::Instance()
{
	static ResourceManager instance;
	return instance;
}