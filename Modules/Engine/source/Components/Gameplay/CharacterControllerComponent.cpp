// CharacterControllerComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Engine/Components/Gameplay/CharacterControllerComponent.h"
#include "../../../include/Engine/World.h"
#include "../../../include/Engine/Systems/PhysicsSystem.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::CharacterControllerComponent)
.Data("Collider", &CharacterControllerComponent::_collider);

namespace Willow
{
	bool CharacterControllerComponent::OnGround() const
	{
		bool out = false;
		this->GetWorld().GetSystem<PhysicsSystem>()->CharacterControllerOnGround(*this, out);
		return out;
	}

	void CharacterControllerComponent::Jump()
	{
		this->GetWorld().GetSystem<PhysicsSystem>()->CharacterControllerJump(*this);
	}

	void CharacterControllerComponent::Walk(const Vec2& direction)
	{
		this->GetWorld().GetSystem<PhysicsSystem>()->CharacterControllerWalk(*this, direction);
	}

	///////////////////
	///   Methods   ///

	void CharacterControllerComponent::SetCollider(PrimitiveColliderComponent* collider)
	{
		// If the collider exists and its not connected to the same Entity
		if (collider && &collider->GetEntity() == &this->GetEntity())
		{
			// Invalid configuration
			return;
		}

		_collider = collider;
		// TODO: Notify physics system
	}
	
	void CharacterControllerComponent::OnInitialize()
	{
		this->Base::OnInitialize();
		this->Create();
	}

	void CharacterControllerComponent::Create()
	{
		if (!_collider.IsNull())
		{
			this->GetWorld().GetSystem<PhysicsSystem>()->CreateCharacterController(*this, this->GetEntity(), _collider, _settings);
		}
	}
}
