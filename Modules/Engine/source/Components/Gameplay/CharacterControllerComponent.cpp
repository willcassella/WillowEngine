// CharacterControllerComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Engine/Components/Gameplay/CharacterControllerComponent.h"
#include "../../../include/Engine/World.h"
#include "../../../include/Engine/Systems/PhysicsSystem.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::CharacterControllerComponent)
.Data("collider", &CharacterControllerComponent::_collider);

namespace willow
{
	bool CharacterControllerComponent::on_ground() const
	{
		bool out = false;
		this->get_world().get_system<PhysicsSystem>()->character_controller_on_ground(*this, out);
		return out;
	}

	void CharacterControllerComponent::jump()
	{
		this->get_world().get_system<PhysicsSystem>()->character_controller_jump(*this);
	}

	void CharacterControllerComponent::walk(const Vec2& direction)
	{
		this->get_world().get_system<PhysicsSystem>()->character_controller_walk(*this, direction);
	}

	///////////////////
	///   Methods   ///

	void CharacterControllerComponent::set_collider(PrimitiveColliderComponent* collider)
	{
		// If the collider exists and its not connected to the same Entity
		if (collider && &collider->get_entity() != &this->get_entity())
		{
			// Invalid configuration
			return;
		}

		this->_collider = collider;

		if (this->_is_active)
		{
			this->get_world().get_system<PhysicsSystem>()->set_character_controller_collider(*this, this->_collider);
		}
		else
		{
			this->create();
		}
	}
	
	void CharacterControllerComponent::on_initialize()
	{
		this->Base::on_initialize();
		this->create();
	}

	void CharacterControllerComponent::on_destroy()
	{
		if (this->_is_active)
		{
			this->get_world().get_system<PhysicsSystem>()->destroy_character_controller(*this);
		}
	}

	void CharacterControllerComponent::create()
	{
		if (!this->_collider.is_null())
		{
			this->get_world().get_system<PhysicsSystem>()->create_character_controller(*this, this->get_entity(), this->_collider, this->_settings);
			this->_is_active = true;
		}
	}
}
