// PhysicsBody.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../include/BulletPhysics/Forwards.h"
#include "Common.h"

namespace willow
{
	/////////////////
	///   Types   ///

	class RigidBody final : public btRigidBody
	{
		////////////////////////
		///   Constructors   ///
	public:

		RigidBody(EntityPhysicsData& entityData);
		RigidBody(const RigidBody& copy) = delete;

		///////////////////
		///   Methods   ///
	public:

		void disable(EntityPhysicsData& entityData);
	};
}
