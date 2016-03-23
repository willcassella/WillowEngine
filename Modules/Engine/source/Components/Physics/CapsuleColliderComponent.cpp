// CapsuleColliderComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Engine/World.h"
#include "../../../include/Engine/Components/Physics/CapsuleColliderComponent.h"
#include "../../Physics/Physics.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::CapsuleColliderComponent)
.Property("Radius", &CapsuleColliderComponent::GetRadius, &CapsuleColliderComponent::EDITOR_SetRadius, "", "Capsule")
.Property("Height", &CapsuleColliderComponent::GetHeight, &CapsuleColliderComponent::EDITOR_SetHeight, "", "Capsule")
.Property("Axis", &CapsuleColliderComponent::GetAxis, &CapsuleColliderComponent::EDITOR_SetAxis, "", "Capsule");

namespace Willow
{
	/////////////////////
	///   Constants   ///

	constexpr float CapsuleColliderComponent::DefaultRadius;

	constexpr float CapsuleColliderComponent::DefaultHeight;

	constexpr ColliderComponent::Axis CapsuleColliderComponent::DefaultAxis;

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
		Base::ToArchive(writer);
		writer.PushValue("Radius", this->GetRadius());
		writer.PushValue("Height", this->GetHeight());
		//writer.PushValue("Axis", this->GetAxis());
	}

	void CapsuleColliderComponent::FromArchive(const ArchiveReader& reader)
	{
		Base::FromArchive(reader);
		
		auto radius = this->GetRadius();
		auto height = this->GetHeight();
		auto axis = this->GetAxis();
		reader.PullValue("Radius", radius);
		reader.PullValue("Height", height);
		//reader.PullValue("Axis", axis);

		if (radius != this->GetRadius() || height != this->GetHeight() || axis != this->GetAxis())
		{	
			this->Set(radius, height, axis);
		}
	}

	float CapsuleColliderComponent::GetRadius() const
	{
		return _shape ? _shape->getRadius() : DefaultRadius;
	}

	void CapsuleColliderComponent::SetRadius(float radius, UpdateEntityColliderOptions updateOptions)
	{
		auto height = this->GetHeight();
		auto axis = this->GetAxis();
		this->Set(radius, height, axis, updateOptions);
	}

	float CapsuleColliderComponent::GetHeight() const
	{
		return _shape ? _shape->getHalfHeight() * 2 : DefaultHeight;
	}

	void CapsuleColliderComponent::SetHeight(float height, UpdateEntityColliderOptions updateOptions)
	{
		auto radius = this->GetRadius();
		auto axis = this->GetAxis();
		this->Set(radius, height, axis, updateOptions);
	}

	ColliderComponent::Axis CapsuleColliderComponent::GetAxis() const
	{
		return _shape ? static_cast<Axis>(_shape->getUpAxis()) : DefaultAxis;
	}

	void CapsuleColliderComponent::SetAxis(Axis axis, UpdateEntityColliderOptions updateOptions)
	{
		auto radius = this->GetRadius();
		auto height = this->GetHeight();
		this->Set(radius, height, axis, updateOptions);
	}

	void CapsuleColliderComponent::Set(float radius, float height, Axis axis, UpdateEntityColliderOptions updateOptions)
	{
		auto isActive = this->IsActive();
		
		if (isActive)
		{
			this->DeactivateCollider(UpdateNothing);
		}

		switch (axis)
		{
		case Axis::X:
			_shape = std::make_unique<btCapsuleShapeX>(radius, height);
			break;
		case Axis::Y:
			_shape = std::make_unique<btCapsuleShape>(radius, height);
			break;
		case Axis::Z:
			_shape = std::make_unique<btCapsuleShapeZ>(radius, height);
			break;
		}
		
		if (isActive)
		{
			this->ActivateCollider(updateOptions);
		}
	}

	void CapsuleColliderComponent::OnSpawn()
	{
		if (!_shape)
		{
			_shape = std::make_unique<btCapsuleShape>(DefaultRadius, DefaultHeight);
		}

		Base::OnSpawn();
	}

	btCollisionShape* CapsuleColliderComponent::GetCollisionShape() const
	{
		return _shape.get();
	}

	void CapsuleColliderComponent::EDITOR_SetRadius(float radius)
	{
		this->SetRadius(radius, UpdateAll);
	}

	void CapsuleColliderComponent::EDITOR_SetHeight(float height)
	{
		this->SetHeight(height, UpdateAll);
	}

	void CapsuleColliderComponent::EDITOR_SetAxis(Axis axis)
	{
		this->SetAxis(axis, UpdateAll);
	}
}
