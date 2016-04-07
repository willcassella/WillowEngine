// CapsuleColliderComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Engine/World.h"
#include "../../../include/Engine/Components/Physics/CapsuleColliderComponent.h"
#include "../../../include/Engine/Systems/PhysicsSystem.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::CapsuleColliderComponent)
.Property("Radius", &CapsuleColliderComponent::GetRadius, &CapsuleColliderComponent::SetRadius, "", "Capsule")
.Property("Height", &CapsuleColliderComponent::GetHeight, &CapsuleColliderComponent::SetHeight, "", "Capsule")
.Property("Axis", &CapsuleColliderComponent::GetAxis, &CapsuleColliderComponent::SetAxis, "", "Capsule");

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	CapsuleColliderComponent::CapsuleColliderComponent()
	{
		// All done
	}

	CapsuleColliderComponent::~CapsuleColliderComponent()
	{
		// All done
	}

	///////////////////
	///   Methods   ///

	void CapsuleColliderComponent::ToArchive(ArchiveWriter& writer) const
	{
		this->Base::ToArchive(writer);
		writer.PushValue("Radius", this->GetRadius());
		writer.PushValue("Height", this->GetHeight());
		//writer.PushValue("Axis", this->GetAxis());
	}

	void CapsuleColliderComponent::FromArchive(const ArchiveReader& reader)
	{
		this->Base::FromArchive(reader);
		reader.PullValue("Radius", _shape.Radius);
		reader.PullValue("Height", _shape.Height);
		//reader.PullValue("Axis", _shape.Axis);
		this->UpdateShape();
	}

	void CapsuleColliderComponent::SetRadius(float radius)
	{
		_shape.Radius = radius;
		this->UpdateShape();
	}

	void CapsuleColliderComponent::SetHeight(float height)
	{
		_shape.Height = height;
		this->UpdateShape();
	}

	void CapsuleColliderComponent::SetAxis(ShapeAxis axis)
	{
		_shape.Axis = axis;
		this->UpdateShape();
	}

	void CapsuleColliderComponent::SetShape(Shape shape)
	{
		_shape = shape;
		this->UpdateShape();
	}

	void CapsuleColliderComponent::OnUpdateColliderTransform()
	{
		this->GetWorld().GetSystem<PhysicsSystem>()->SetColliderTransform(*this, this->GetColliderTransform());
	}

	bool CapsuleColliderComponent::OnActivate()
	{
		this->GetWorld().GetSystem<PhysicsSystem>()->CreateCollider(*this, this->GetEntity(), this->GetColliderTransform(), _shape);
		return true;
	}

	void CapsuleColliderComponent::OnDeactivate()
	{
		this->GetWorld().GetSystem<PhysicsSystem>()->DestroyCollider(*this);
	}

	void CapsuleColliderComponent::UpdateShape()
	{
		if (this->HasSpawned() && this->IsActive())
		{
			this->GetWorld().GetSystem<PhysicsSystem>()->SetColliderShape(*this, _shape);
		}
	}
}
