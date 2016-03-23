// PhysicsBody.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <btBulletDynamicsCommon.h>
#include "Physics.h"

namespace Willow
{
	/** Manages the Bullet Physics state for an Entity. */
	class PhysicsBody final : public btMotionState
	{
		////////////////////////
		///   Constructors   ///
	public:

		PhysicsBody(Entity& entity)
			: _entity(&entity)
		{
			// All done
		}

		//////////////////
		///   Fields   ///
	public:

		std::unique_ptr<btCollisionObject> Body;

		///////////////////
		///   Methods   ///
	public:

		void getWorldTransform(btTransform& worldTransform) const override
		{
			// Get the world location and assign it to Bullet
			worldTransform.setOrigin(ConvertToBullet(_entity->GetWorldLocation()));

			// Get the world rotation and assign it to Bullet
			worldTransform.setRotation(ConvertToBullet(_entity->GetWorldRotation()));
		}

		void setWorldTransform(const btTransform& worldTransform) override
		{
			// Set the world location from Bullet
			_entity->SetWorldLocation(ConvertFromBullet(worldTransform.getOrigin()));

			// Set the world rotation from Bullet
			_entity->SetWorldRotation(ConvertFromBullet(worldTransform.getRotation()));
		}

		////////////////
		///   Data   ///
	private:

		Entity* _entity;
	};
}
