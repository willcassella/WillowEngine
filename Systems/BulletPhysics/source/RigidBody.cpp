// RigidBody.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../private/RigidBody.h"
#include "../private/GhostBody.h"
#include "../private/EntityPhysicsData.h"

namespace willow
{
	////////////////////////
	///   Constructors   ///

	RigidBody::RigidBody(EntityPhysicsData& entityData)
		: btRigidBody{ entityData.state.mass, &entityData, &entityData.collider }
	{
		// Set the mass and inertia
		btVector3 inertia;
		entityData.collider.calculateLocalInertia(entityData.state.mass, inertia);
		this->setMassProps(entityData.state.mass, inertia);

		// Set other properties
		this->setLinearFactor(convert_to_bullet(entityData.state.linear_motion_factor));
		this->setAngularFactor(convert_to_bullet(entityData.state.angular_motion_factor));
		this->setFriction(entityData.state.friction);
		this->setRollingFriction(entityData.state.rolling_friction);

		if (entityData.ghost_body)
		{
			this->setIgnoreCollisionCheck(entityData.ghost_body, true);
			entityData.ghost_body->setIgnoreCollisionCheck(this, true);
		}
	}

	void RigidBody::disable(EntityPhysicsData& entityData)
	{
		if (entityData.ghost_body)
		{
			this->setIgnoreCollisionCheck(entityData.ghost_body, false);
			entityData.ghost_body->setIgnoreCollisionCheck(this, false);
		}
	}
}
