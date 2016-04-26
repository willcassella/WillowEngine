// EntityPhysicsData.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../private/EntityPhysicsData.h"
#include "../private/RigidBody.h"
#include "../private/GhostBody.h"

namespace willow
{
	////////////////////////
	///   Constructors   ///

	EntityPhysicsData::EntityPhysicsData(const Entity::PhysicsState& state, Entity::PhysicsMode mode, Handle<Entity> entity, Handle<Entity> parent, willow::Transform& transform)
		: state{ state }, 
		mode{ mode }, 
		entity{ entity },
		parent{ parent }, 
		transform{ &transform }
	{
		this->collider.setLocalScaling(convert_to_bullet(transform.scale));
	}

	///////////////////
	///   Methods   ///

	void EntityPhysicsData::getWorldTransform(btTransform& worldTrans) const
	{
		worldTrans.setOrigin(convert_to_bullet(this->transform->location));
		worldTrans.setRotation(convert_to_bullet(this->transform->rotation));
	}

	void EntityPhysicsData::setWorldTransform(const btTransform& worldTrans)
	{
		// Use temporaries, makes debugging easier
		const auto newLocation = convert_from_bullet(worldTrans.getOrigin());
		const auto newRotation = convert_from_bullet(worldTrans.getRotation());

		this->transform->location = newLocation;
		this->transform->rotation = newRotation;
		this->ghost_body->setWorldTransform(worldTrans);
	}

	void EntityPhysicsData::update_inertia()
	{
		if (this->rigid_body && this->mode == Entity::PhysicsMode::Dynamic)
		{
			const auto mass = this->state.mass;
			btVector3 inertia;

			// Calculate inertia
			this->collider.calculateLocalInertia(mass, inertia);

			// Apply it
			this->rigid_body->setMassProps(mass, inertia);
		}
	}
}
