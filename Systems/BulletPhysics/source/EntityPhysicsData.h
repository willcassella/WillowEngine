// EntityPhysicsData.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <Engine/GHandle.h>
#include "EntityCollider.h"

namespace Willow
{
	struct EntityPhysicsData final : btMotionState
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
		Willow::RigidBody* RigidBody = nullptr;

		/** The PhysicsState of this Entity. */
		Entity::PhysicsState State;

		/** The mode this Entity is currently in. */
		Entity::PhysicsMode Mode = Entity::PhysicsMode::Transient;

		/** The parent of this Entity. */
		EntityHandle Parent;

		/** The Transform for this Entity. */
		Willow::Transform* Transform = nullptr;

		///////////////////
		///   Methods   ///
	public:

		void getWorldTransform(btTransform& worldTrans) const override
		{
			worldTrans.setOrigin(ConvertToBullet(Transform->Location));
			worldTrans.setRotation(ConvertToBullet(Transform->Rotation));
		}

		void setWorldTransform(const btTransform& worldTrans) override
		{
			// Use temporaries, makes debugging easier
			const auto newLocation = ConvertFromBullet(worldTrans.getOrigin());
			const auto newRotation = ConvertFromBullet(worldTrans.getRotation());

			Transform->Location = newLocation;
			Transform->Rotation = newRotation;
		}
	};
}
