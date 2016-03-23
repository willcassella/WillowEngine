// SphereColliderComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Engine/Components/Physics/SphereColliderComponent.h"
#include "../../Physics/Physics.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::SphereColliderComponent)
.Property("Radius", &SphereColliderComponent::GetRadius, &SphereColliderComponent::EDITOR_SetRadius, "", "Sphere");

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	SphereColliderComponent::SphereColliderComponent()
	{
		// All done
	}

	SphereColliderComponent::~SphereColliderComponent()
	{
		// All done
	}

	///////////////////
	///   Methods   ///

	void SphereColliderComponent::ToArchive(ArchiveWriter& writer) const
	{
		Base::ToArchive(writer);
		writer.PushValue("Radius", this->GetRadius());
	}

	void SphereColliderComponent::FromArchive(const ArchiveReader& reader)
	{
		Base::FromArchive(reader);

		auto radius = this->GetRadius();
		reader.PullValue("Radius", radius);
		
		if (radius != this->GetRadius())
		{
			this->SetRadius(radius);
		}
	}

	float SphereColliderComponent::GetRadius() const
	{
		return _shape ? _shape->getRadius() : DefaultRadius;
	}

	void SphereColliderComponent::SetRadius(float radius, UpdateEntityColliderOptions updateOptions)
	{
		auto isActive = this->IsActive();

		if (isActive)
		{
			this->DeactivateCollider(UpdateNothing);
		}

		_shape = std::make_unique<btSphereShape>(radius);
		
		if (isActive)
		{
			this->ActivateCollider(updateOptions);
		}
	}

	void SphereColliderComponent::OnSpawn()
	{
		if (!_shape)
		{
			_shape = std::make_unique<btSphereShape>(DefaultRadius);
		}

		this->Base::OnSpawn();
	}

	btCollisionShape* SphereColliderComponent::GetCollisionShape() const
	{
		return _shape.get();
	}

	void SphereColliderComponent::EDITOR_SetRadius(float radius)
	{
		this->SetRadius(radius, UpdateAll);
	}
}
