// EntityPhysicsData.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <Engine/Handle.h>
#include <Engine/Entity.h>
#include "EntityCollider.h"

namespace Willow
{
	class EntityPhysicsData final : public btMotionState
	{
		////////////////////////
		///   Constructors   ///
	public:

		EntityPhysicsData(const Entity::PhysicsState& state, Entity::PhysicsMode mode, EntityHandle parent, Transform& transform);
		EntityPhysicsData(const EntityPhysicsData& copy) = delete;

		//////////////////
		///   Fields   ///
	public:

		/** The collider for this Entity. */
		EntityCollider Collider;

		/** GhostBody for this Entity.
		* NOTE: This will exist if:
		* - The Entity is in the 'Ghost', 'Kinematic', or 'Dynamic' modes. */
		class GhostBody* GhostBody = nullptr;

		/** RigidBody for this Entity.
		* NOTE: This will exist if:
		* - The Entity is in the 'Kinematic' or 'Dynamic' modes.
		* - The Entity has any constraints attached to it. */
		class RigidBody* RigidBody = nullptr;

		/** The PhysicsState of this Entity. */
		Entity::PhysicsState State;

		/** The mode this Entity is currently in. */
		Entity::PhysicsMode Mode = Entity::PhysicsMode::Transient;

		/** The parent of this Entity. */
		EntityHandle Parent;

		/** The Transform for this Entity. */
		Willow::Transform* Transform;

		///////////////////
		///   Methods   ///
	public:

		void getWorldTransform(btTransform& worldTrans) const override;

		void setWorldTransform(const btTransform& worldTrans) override;
	};
}
