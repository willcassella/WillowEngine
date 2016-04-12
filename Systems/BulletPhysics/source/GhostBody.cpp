// GhostBody.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../private/GhostBody.h"
#include "../private/RigidBody.h"

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	GhostBody::GhostBody(EntityPhysicsData& entityData)
	{
		this->setCollisionFlags(this->getCollisionFlags() | CF_NO_CONTACT_RESPONSE);
		this->btPairCachingGhostObject::setCollisionShape(&entityData.Collider);
		entityData.GhostBody = this;

		// Set transform
		const btTransform transform{ ConvertToBullet(entityData.Transform->Rotation), ConvertToBullet(entityData.Transform->Location) };
		this->setWorldTransform(transform);

		if (entityData.RigidBody)
		{
			this->setIgnoreCollisionCheck(entityData.RigidBody, true);
			entityData.RigidBody->setIgnoreCollisionCheck(this, true);
		}
	}

	void GhostBody::Disable(EntityPhysicsData& entityData)
	{
		if (entityData.RigidBody)
		{
			this->setIgnoreCollisionCheck(entityData.RigidBody, false);
			entityData.RigidBody->setIgnoreCollisionCheck(this, false);
		}

		entityData.GhostBody = nullptr;
	}
}
