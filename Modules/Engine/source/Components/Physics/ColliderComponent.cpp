// ColliderComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Engine/Components/Physics/ColliderComponent.h"
#include "../../Physics/EntityCollider.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::ColliderComponent)
.Data("IsActive", &ColliderComponent::_isActive)
.Data("ColliderTransform", &ColliderComponent::_colliderTransform)
.Property("IsActive", &ColliderComponent::IsActive, &ColliderComponent::EDITOR_SetActive, "", "Collider", PF_EditorOnly)
.Property("Location", &ColliderComponent::GetColliderLocation, &ColliderComponent::EDITOR_SetColliderLocation, "", "Collider")
.Property("Rotation", &ColliderComponent::GetColliderRotation, &ColliderComponent::EDITOR_SetColliderRotation, "", "Collider")
.Property("Scale", &ColliderComponent::GetColliderScale, &ColliderComponent::EDITOR_SetColliderScale, "", "Collider");

BUILD_ENUM_REFLECTION(Willow::ColliderComponent::Axis)
.Value("X", Willow::ColliderComponent::Axis::X)
.Value("Y", Willow::ColliderComponent::Axis::Y)
.Value("Z", Willow::ColliderComponent::Axis::Z);

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	ColliderComponent::ColliderComponent()
		: _isActive{ true }
	{
		// All done
	}

	///////////////////
	///   Methods   ///

	void ColliderComponent::ActivateCollider(UpdateEntityColliderOptions updateOptions)
	{
		if (this->IsActive())
		{
			// We're already activated
			return;
		}

		_isActive = true;

		if (!this->HasSpawned() || this->IsDestroyed())
		{
			// We'll add the shape once we're spawning
			return;
		}

		auto shape = this->GetCollisionShape();
		if (!shape)
		{
			// The shape doesn't exist, so it can't be activated
			_isActive = false;
			return;
		}

		// Add the shape and update the EntityCollider
		this->GetEntity().INTERNAL_GetCollider()->AddChild(*shape, this->GetColliderLocation(), this->GetColliderRotation());
		this->UpdateEntityCollider(updateOptions);
	}

	void ColliderComponent::DeactivateCollider(UpdateEntityColliderOptions updateOptions)
	{
		if (!this->IsActive())
		{
			// We're already deactivated
			return;
		}

		_isActive = false;

		if (!this->HasSpawned() || this->IsDestroyed())
		{
			return;
		}

		this->GetEntity().INTERNAL_GetCollider()->RemoveChild(*this->GetCollisionShape());
		this->UpdateEntityCollider(updateOptions);
	}

	void ColliderComponent::SetColliderTransform(const Transform& transform, UpdateEntityColliderOptions updateOptions)
	{
		_colliderTransform = transform;

		// If we're not spawned or activated
		if (!this->HasSpawned() || !this->IsActive())
		{
			return;
		}

		auto& shape = *this->GetCollisionShape();
		shape.setLocalScaling(ConvertToBullet(transform.GetScale()));
		this->GetEntity().INTERNAL_GetCollider()->UpdateChildLocationRotation(shape, transform.GetLocation(), transform.GetRotation());
		this->UpdateEntityCollider(updateOptions);
	}

	void ColliderComponent::SetColliderLocation(const Vec3& location, UpdateEntityColliderOptions updateOptions)
	{
		_colliderTransform.SetLocation(location);

		// If we're not spawned or activated
		if (!this->IsInitialized() || !this->IsActive())
		{
			return;
		}

		this->GetEntity().INTERNAL_GetCollider()->UpdateChildLocationRotation(*this->GetCollisionShape(), location, this->GetColliderRotation());
		this->UpdateEntityCollider(updateOptions);
	}

	void ColliderComponent::SetColliderRotation(const Quat& rotation, UpdateEntityColliderOptions updateOptions)
	{
		_colliderTransform.SetRotation(rotation);

		// If we're not spawned or activated
		if (!this->HasSpawned() || !this->IsActive())
		{
			return;
		}

		this->GetEntity().INTERNAL_GetCollider()->UpdateChildLocationRotation(*this->GetCollisionShape(), this->GetColliderLocation(), rotation);
		this->UpdateEntityCollider(updateOptions);
	}

	void ColliderComponent::SetColliderScale(const Vec3& scale, UpdateEntityColliderOptions updateOptions)
	{
		_colliderTransform.SetScale(scale);

		// If we're not spawned, or activated
		if (!this->HasSpawned() || !this->IsActive())
		{
			return;
		}

		this->GetCollisionShape()->setLocalScaling(ConvertToBullet(scale));
		this->UpdateEntityCollider(updateOptions);
	}

	void ColliderComponent::UpdateEntityCollider(UpdateEntityColliderOptions updateOptions)
	{
		if (updateOptions == UpdateNothing)
		{
			return;
		}

		auto& entity = this->GetEntity();

		if (updateOptions & UpdateAABB)
		{
			entity.INTERNAL_GetCollider()->recalculateLocalAabb();
		}

		if (updateOptions & UpdateInertia)
		{
			entity.INTERNAL_UpdateInertia();
		}
	}

	void ColliderComponent::OnSpawn()
	{
		Base::OnSpawn();
		
		if (_isActive)
		{
			auto shape = this->GetCollisionShape();

			if (!shape)
			{
				// The shape doesn't exist, so we can't be activated
				_isActive = false;
				return;
			}

			shape->setLocalScaling(ConvertToBullet(this->GetColliderScale()));
			this->GetEntity().INTERNAL_GetCollider()->AddChild(*shape, this->GetColliderLocation(), this->GetColliderRotation());
			this->UpdateEntityCollider(UpdateAll);
		}
	}

	void ColliderComponent::OnDestroy()
	{
		Base::OnDestroy();

		if (_isActive)
		{
			this->GetEntity().INTERNAL_GetCollider()->RemoveChild(*this->GetCollisionShape());
			_isActive = false;
		}
	}

	void ColliderComponent::EDITOR_SetActive(bool enabled)
	{
		if (enabled)
		{
			this->ActivateCollider(UpdateAll);
		}
		else
		{
			this->DeactivateCollider(UpdateAll);
		}
	}

	void ColliderComponent::EDITOR_SetColliderLocation(const Vec3& location)
	{
		this->SetColliderLocation(location, UpdateAll);
	}

	void ColliderComponent::EDITOR_SetColliderRotation(const Quat& rotation)
	{
		this->SetColliderRotation(rotation, UpdateAll);
	}

	void ColliderComponent::EDITOR_SetColliderScale(const Vec3& scale)
	{
		this->SetColliderScale(scale, UpdateAll);
	}
}
