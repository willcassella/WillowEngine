// GhostBody.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include "../include/BulletPhysics/Forwards.h"

namespace willow
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

		void disable(EntityPhysicsData& entityData);
	};
}
