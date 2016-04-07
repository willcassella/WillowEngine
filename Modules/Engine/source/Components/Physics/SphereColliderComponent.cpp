// SphereColliderComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Engine/Components/Physics/SphereColliderComponent.h"
#include "../../../include/Engine/World.h"
#include "../../../include/Engine/Systems/PhysicsSystem.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::SphereColliderComponent)
.Property("Radius", &SphereColliderComponent::GetRadius, &SphereColliderComponent::SetRadius, "", "Sphere");

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
		this->Base::ToArchive(writer);
		writer.PushValue("Radius", this->GetRadius());
	}

	void SphereColliderComponent::FromArchive(const ArchiveReader& reader)
	{
		this->Base::FromArchive(reader);
		reader.PullValue("Radius", _shape.Radius);
		this->UpdateShape();
	}

	void SphereColliderComponent::SetRadius(float radius)
	{
		_shape.Radius = radius;
		this->UpdateShape();
	}

	void SphereColliderComponent::OnUpdateColliderTransform()
	{
		this->GetWorld().GetSystem<PhysicsSystem>()->SetColliderTransform(*this, this->GetColliderTransform());
	}

	bool SphereColliderComponent::OnActivate()
	{
		this->GetWorld().GetSystem<PhysicsSystem>()->CreateCollider(*this, this->GetEntity(), this->GetColliderTransform(), _shape);
		return true;
	}

	void SphereColliderComponent::OnDeactivate()
	{
		this->GetWorld().GetSystem<PhysicsSystem>()->DestroyCollider(*this);
	}

	void SphereColliderComponent::UpdateShape()
	{
		if (this->HasSpawned() && this->IsActive())
		{
			this->GetWorld().GetSystem<PhysicsSystem>()->SetColliderShape(*this, _shape);
		}
	}
}
