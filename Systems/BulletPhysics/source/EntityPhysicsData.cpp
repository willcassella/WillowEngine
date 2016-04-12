// EntityPhysicsData.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../private/EntityPhysicsData.h"
#include "../private/RigidBody.h"
#include "../private/GhostBody.h"

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	EntityPhysicsData::EntityPhysicsData(const Entity::PhysicsState& state, Entity::PhysicsMode mode, EntityHandle parent, Willow::Transform& transform)
		: State{ state }, Mode{ mode }, Parent{ parent }, Transform{ &transform }
	{
		this->Collider.setLocalScaling(ConvertToBullet(transform.Scale));
	}

	///////////////////
	///   Methods   ///

	void EntityPhysicsData::getWorldTransform(btTransform& worldTrans) const
	{
		worldTrans.setOrigin(ConvertToBullet(Transform->Location));
		worldTrans.setRotation(ConvertToBullet(Transform->Rotation));
	}

	void EntityPhysicsData::setWorldTransform(const btTransform& worldTrans)
	{
		// Use temporaries, makes debugging easier
		const auto newLocation = ConvertFromBullet(worldTrans.getOrigin());
		const auto newRotation = ConvertFromBullet(worldTrans.getRotation());

		Transform->Location = newLocation;
		Transform->Rotation = newRotation;
		GhostBody->setWorldTransform(worldTrans);
	}
}
