// ColliderComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Engine/Components/Physics/ColliderComponent.h"
#include "../../../include/Engine/World.h"
#include "../../../include/Engine/Systems/PhysicsSystem.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::ColliderComponent)
.Data("IsActive", &ColliderComponent::_isActive)
.Data("ColliderTransform", &ColliderComponent::_colliderTransform)
.Property("IsActive", &ColliderComponent::IsActive, &ColliderComponent::EDITOR_SetActive, "", "Collider", PF_EditorOnly)
.Property("Location", &ColliderComponent::GetColliderLocation, &ColliderComponent::SetColliderLocation, "", "Collider")
.Property("Rotation", &ColliderComponent::GetColliderRotation, &ColliderComponent::SetColliderRotation, "", "Collider")
.Property("Scale", &ColliderComponent::GetColliderScale, &ColliderComponent::SetColliderScale, "", "Collider");

BUILD_ENUM_REFLECTION(Willow::ColliderComponent::ShapeAxis)
.Value("X", Willow::ColliderComponent::ShapeAxis::X)
.Value("Y", Willow::ColliderComponent::ShapeAxis::Y)
.Value("Z", Willow::ColliderComponent::ShapeAxis::Z);

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

	void ColliderComponent::ActivateCollider()
	{
		if (this->IsActive())
		{
			// We're already activated
			return;
		}

		if (!this->HasSpawned() || this->IsDestroyed())
		{
			// We'll activate once we spawn
			_isActive = true;
			return;
		}

		// Attempt to activate
		_isActive = this->OnActivate();
	}

	void ColliderComponent::DeactivateCollider()
	{
		if (!this->IsActive())
		{
			// We're already deactivated
			return;
		}

		if (!this->HasSpawned() || this->IsDestroyed())
		{
			// We haven't spawned yet, so nothing to undo
			_isActive = false;
			return;
		}

		this->OnDeactivate();
	}

	void ColliderComponent::SetColliderTransform(const Transform& transform)
	{
		_colliderTransform = transform;
		this->UpdateColliderTransform();
	}

	void ColliderComponent::SetColliderLocation(const Vec3& location)
	{
		_colliderTransform.Location = location;
		this->UpdateColliderTransform();
	}

	void ColliderComponent::SetColliderRotation(const Quat& rotation)
	{
		_colliderTransform.Rotation = rotation;
		this->UpdateColliderTransform();
	}

	void ColliderComponent::SetColliderScale(const Vec3& scale)
	{
		_colliderTransform.Scale = scale;
		this->UpdateColliderTransform();
	}

	void ColliderComponent::OnInitialize()
	{
		this->Base::OnSpawn();

		if (this->IsActive())
		{
			_isActive = this->OnActivate();
		}
	}

	void ColliderComponent::OnDestroy()
	{
		this->Base::OnDestroy();

		if (this->IsActive())
		{
			this->OnDeactivate();
		}
	}

	void ColliderComponent::UpdateColliderTransform()
	{
		if (this->IsActive() && this->HasSpawned())
		{
			this->OnUpdateColliderTransform();
		}
	}

	void ColliderComponent::EDITOR_SetActive(bool enabled)
	{
		if (enabled)
		{
			this->ActivateCollider();
		}
		else
		{
			this->DeactivateCollider();
		}
	}
}
