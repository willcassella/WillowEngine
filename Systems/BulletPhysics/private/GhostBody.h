// GhostBody.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include "EntityPhysicsData.h"

namespace Willow
{
	class GhostBody final : public btPairCachingGhostObject
	{
		////////////////////////
		///   Constructors   ///
	public:

		GhostBody(EntityPhysicsData& entityData);
		GhostBody(const GhostBody& copy) = delete;

		///////////////////
		///   Methods   ///
	public:

		void Disable(EntityPhysicsData& entityData);
	};
}
