// EntityPhysicsData.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Handle.h>
#include <Engine/Entity.h>
#include "../include/BulletPhysics/Forwards.h"
#include "EntityCollider.h"

namespace willow
{
	class EntityPhysicsData final : public btMotionState
	{
		////////////////////////
		///   Constructors   ///
	public:

		EntityPhysicsData(const Entity::PhysicsState& state, Entity::PhysicsMode mode, Handle<Entity> entity, Handle<Entity> parent, Transform& transform);
		EntityPhysicsData(const EntityPhysicsData& copy) = delete;

		//////////////////
		///   Fields   ///
	public:

		/** The collider for this Entity. */
		EntityCollider collider;

		/** GhostBody for this Entity.
		* NOTE: This will exist if:
		* - The Entity is in the 'Ghost', 'Kinematic', or 'Dynamic' modes. */
		GhostBody* ghost_body = nullptr;

		/** RigidBody for this Entity.
		* NOTE: This will exist if:
		* - The Entity is in the 'Kinematic' or 'Dynamic' modes.
		* - The Entity has any constraints attached to it. */
		RigidBody* rigid_body = nullptr;

		/** The PhysicsState of this Entity. */
		Entity::PhysicsState state;

		/** The mode this Entity is currently in. */
		Entity::PhysicsMode mode = Entity::PhysicsMode::Transient;

		/** The entity this belongs to. */
		Handle<Entity> entity;

		/** The parent of this Entity. */
		Handle<Entity> parent;

		/** The Transform for this Entity. */
		Transform* transform;

		///////////////////
		///   Methods   ///
	public:

		void getWorldTransform(btTransform& worldTrans) const override;

		void setWorldTransform(const btTransform& worldTrans) override;

		void update_inertia();
	};
}
