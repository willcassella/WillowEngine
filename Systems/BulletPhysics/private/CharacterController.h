// CharacterController.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <Engine/Components/Gameplay/CharacterControllerComponent.h>
#include "GhostBody.h"

namespace Willow
{
	class CharacterController final : public btKinematicCharacterController
	{
		////////////////////////
		///   Constructors   ///
	public:

		CharacterController(EntityPhysicsData& entityData, btConvexShape& collider, const CharacterControllerComponent::Settings& settings)
			: btKinematicCharacterController{ entityData.GhostBody, &collider, 1 }
		{
			_entityData = &entityData;
		}

		///////////////////
		///   Methods   ///
	public:

		/** Updates this CharacterController. */
		void updateAction(btCollisionWorld* world, btScalar deltaTimeStep) override
		{
			// Call base implementation
			this->btKinematicCharacterController::updateAction(world, deltaTimeStep);
			
			// Update entity transform
			auto& transform = this->getGhostObject()->getWorldTransform();
			_entityData->Transform->Location = ConvertFromBullet(transform.getOrigin());
			_entityData->Transform->Rotation = ConvertFromBullet(transform.getRotation());
		}

		/** Reimplementation of 'canJump', allows for double-jumping (engine API only exposes 'OnGround()'). */
		bool canJump() const override
		{
			return true;
		}

		////////////////
		///   Data   ///
	private:

		EntityPhysicsData* _entityData;
	};
}
