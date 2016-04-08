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

		RigidBody(EntityPhysicsData& entityData)
			: btRigidBody{ entityData.State.Mass, &entityData, &entityData.Collider }
		{
			// Set the mass and inertia
			btVector3 inertia;
			entityData.Collider.calculateLocalInertia(entityData.State.Mass, inertia);
			this->setMassProps(entityData.State.Mass, inertia);

			// Set other properties
			this->setLinearFactor(ConvertToBullet(entityData.State.LinearMotionFactor));
			this->setAngularFactor(ConvertToBullet(entityData.State.AngularMotionFactor));
			this->setFriction(entityData.State.Friction);
			this->setRollingFriction(entityData.State.RollingFriction);
		}
		RigidBody(const RigidBody& copy) = delete;
		RigidBody(RigidBody&& move) = delete;
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
