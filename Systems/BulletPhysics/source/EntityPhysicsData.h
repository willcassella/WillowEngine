// EntityPhysicsData.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <Engine/GHandle.h>
#include "RigidBody.h"
#include "EntityCollider.h"

namespace Willow
{
	struct EntityPhysicsData final
	{
		//////////////////
		///   Fields   ///
	public:

		/** The collider for this Entity. */
		EntityCollider Collider;

		/** GhostBody for this Entity.
		* NOTE: This will exist if:
		* - The Entity is in the 'Ghost', 'Kinematic', or 'Dynamic' modes. */
		btGhostObject* GhostBody = nullptr;

		/** RigidBody for this Entity.
		* NOTE: This will exist if:
		* - The Entity is in the 'Kinematic' or 'Dynamic' modes.
		* - The Entity has any constraints attached to it. */
		RigidBody* RigidBody = nullptr;

		/** The PhysicsState of this Entity. */
		Entity::PhysicsState State;

		/** The mode this Entity is currently in. */
		Entity::PhysicsMode Mode = Entity::PhysicsMode::Transient;

		/** The parent of this Entity. */
		EntityHandle Parent;

		/** The Transform for this Entity. */
		Willow::Transform* Transform = nullptr;
	};

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
