// CharacterController.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../private/CharacterController.h"
#include "../private/EntityPhysicsData.h"
#include "../private/GhostBody.h"

namespace willow
{
	////////////////////////
	///   Constructors   ///

	CharacterController::CharacterController(EntityPhysicsData& entityData, btConvexShape& collider, const CharacterControllerComponent::Settings& settings)
		: btKinematicCharacterController{ entityData.ghost_body, &collider, settings.max_jump_height }
	{
		_entityData = &entityData;
	}

	///////////////////
	///   Methods   ///

	void CharacterController::updateAction(btCollisionWorld* world, btScalar deltaTimeStep)
	{
		// Call base implementation
		this->btKinematicCharacterController::updateAction(world, deltaTimeStep);

		// Update entity transform
		auto& transform = this->getGhostObject()->getWorldTransform();
		this->_entityData->transform->location = convert_from_bullet(transform.getOrigin());
		this->_entityData->transform->rotation = convert_from_bullet(transform.getRotation());
	}

	/** Reimplementation of 'canJump', allows for double-jumping (engine API only exposes 'on_ground()'). */
	bool CharacterController::canJump() const
	{
		return true;
	}

	void CharacterController::set_collider(btConvexShape& collider)
	{
		this->m_convexShape = &collider;
		// TODO: Is there more I need to do here?
	}
}
