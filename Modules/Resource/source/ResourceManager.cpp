// ResouceManager.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Resource/ResourceManager.h"

namespace willow
{
	////////////////////////
	///   Constructors   ///

	ResourceManager::ResourceManager()
		: _next_resource_id{ 1 }
	{
		// All done
	}

	///////////////////
	///   Methods   ///

	ResourceManager& ResourceManager::get_instance()
	{
		static ResourceManager instance;
		return instance;
	}
}
