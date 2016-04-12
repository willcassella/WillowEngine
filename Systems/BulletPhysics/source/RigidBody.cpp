// RigidBody.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../private/RigidBody.h"
#include "../private/GhostBody.h"

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	RigidBody::RigidBody(EntityPhysicsData& entityData)
		: btRigidBody{ entityData.State.Mass, &entityData, &entityData.Collider }
	{
		// Set the mass and inertia
		btVector3 inertia;
		entityData.Collider.calculateLocalInertia(entityData.State.Mass, inertia);
		this->setMassProps(entityData.State.Mass, inertia);

		// Set other properties
		this->setLinearFactor(ConvertToBullet(entityData.State.LinearMotionFactor));
		this->setAngularFactor(ConvertToBullet(entityData.State.AngularMotionFactor));
		this->setFriction(entityData.State.Friction);
		this->setRollingFriction(entityData.State.RollingFriction);

		if (entityData.GhostBody)
		{
			this->setIgnoreCollisionCheck(entityData.GhostBody, true);
			entityData.GhostBody->setIgnoreCollisionCheck(this, true);
		}
	}

	void RigidBody::Disable(EntityPhysicsData& entityData)
	{
		if (entityData.GhostBody)
		{
			this->setIgnoreCollisionCheck(entityData.GhostBody, false);
			entityData.GhostBody->setIgnoreCollisionCheck(this, false);
		}
	}
}
