// GhostBody.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../private/GhostBody.h"
#include "../private/RigidBody.h"
#include "../private/EntityPhysicsData.h"

namespace willow
{
	////////////////////////
	///   Constructors   ///

	GhostBody::GhostBody(EntityPhysicsData& entityData)
	{
		this->setCollisionFlags(this->getCollisionFlags() | CF_NO_CONTACT_RESPONSE);
		this->btPairCachingGhostObject::setCollisionShape(&entityData.collider);
		entityData.ghost_body = this;

		// Set transform
		const btTransform transform{ convert_to_bullet(entityData.transform->rotation), convert_to_bullet(entityData.transform->location) };
		this->setWorldTransform(transform);

		if (entityData.rigid_body)
		{
			this->setIgnoreCollisionCheck(entityData.rigid_body, true);
			entityData.rigid_body->setIgnoreCollisionCheck(this, true);
		}
	}

	void GhostBody::disable(EntityPhysicsData& entityData)
	{
		if (entityData.rigid_body)
		{
			this->setIgnoreCollisionCheck(entityData.rigid_body, false);
			entityData.rigid_body->setIgnoreCollisionCheck(this, false);
		}

		entityData.ghost_body = nullptr;
	}
}
