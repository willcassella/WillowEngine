// PhysicsBody.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Entity.h>
#include "EntityCollider.h"
#include "MotionState.h"

namespace Willow
{
	static btDefaultMotionState DefaultMotionState;

	class RigidBody final : public btRigidBody
	{
		////////////////////////
		///   Constructors   ///
	public:

		RigidBody(const Entity::PhysicsState& state, Transform& transform, EntityCollider& collider)
			: btRigidBody{ state.Mass, &DefaultMotionState, &collider }, _motionState{ transform }
		{
			// Set the motion state
			this->setMotionState(&_motionState);

			// Set the mass and inertia
			btVector3 inertia;
			collider.calculateLocalInertia(state.Mass, inertia);
			this->setMassProps(state.Mass, inertia);

			// Set other properties
			this->setLinearFactor(ConvertToBullet(state.LinearMotionFactor));
			this->setAngularFactor(ConvertToBullet(state.AngularMotionFactor));
			this->setFriction(state.Friction);
			this->setRollingFriction(state.RollingFriction);
		}
		RigidBody(const RigidBody& copy) = delete;
		RigidBody(RigidBody&& move) = delete;

		////////////////
		///   Data   ///
	private:

		MotionState _motionState;
	};
}
