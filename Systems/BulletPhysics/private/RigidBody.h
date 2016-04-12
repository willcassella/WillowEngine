// PhysicsBody.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Entity.h>
#include "EntityPhysicsData.h"

namespace Willow
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

		void Disable(EntityPhysicsData& entityData);
	};

	/////////////////////
	///   Functions   ///

	inline void UpdateInertia(EntityPhysicsData& data)
	{
		if (data.RigidBody && data.Mode == Entity::PhysicsMode::Dynamic)
		{
			const auto mass = data.State.Mass;
			btVector3 inertia;

			// Calculate inertia
			data.Collider.calculateLocalInertia(mass, inertia);

			// Apply it
			data.RigidBody->setMassProps(mass, inertia);
		}
	}
}
