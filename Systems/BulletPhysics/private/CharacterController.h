// CharacterController.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <Engine/Components/Gameplay/CharacterControllerComponent.h>
#include "../include/BulletPhysics/Forwards.h"

namespace willow
{
	class CharacterController final : public btKinematicCharacterController
	{
		////////////////////////
		///   Constructors   ///
	public:

		CharacterController(EntityPhysicsData& entityData, btConvexShape& collider, const CharacterControllerComponent::Settings& settings);

		///////////////////
		///   Methods   ///
	public:

		/** Updates this CharacterController. */
		void updateAction(btCollisionWorld* world, btScalar deltaTimeStep) override;

		/** Reimplementation of 'canJump', allows for double-jumping (engine API only exposes 'on_ground()'). */
		bool canJump() const override;

		void set_collider(btConvexShape& collider);

		////////////////
		///   Data   ///
	private:

		EntityPhysicsData* _entityData;
	};
}
