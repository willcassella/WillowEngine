// CapsuleColliderComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Engine/World.h"
#include "../../../include/Engine/Components/Physics/CapsuleColliderComponent.h"
#include "../../../include/Engine/Systems/PhysicsSystem.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::CapsuleColliderComponent)
.Property("radius", &CapsuleColliderComponent::get_radius, &CapsuleColliderComponent::set_radius, "", "Capsule")
.Property("height", &CapsuleColliderComponent::get_height, &CapsuleColliderComponent::set_height, "", "Capsule")
.Property("axis", &CapsuleColliderComponent::get_axis, &CapsuleColliderComponent::set_axis, "", "Capsule");

namespace willow
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
		writer.PushValue("radius", this->get_radius());
		writer.PushValue("height", this->get_height());
		//writer.PushValue("axis", this->get_axis());
	}

	void CapsuleColliderComponent::FromArchive(const ArchiveReader& reader)
	{
		this->Base::FromArchive(reader);
		reader.PullValue("radius", _shape.radius);
		reader.PullValue("height", _shape.height);
		//reader.PullValue("axis", _shape.axis);
		this->update_shape();
	}

	void CapsuleColliderComponent::set_radius(float radius)
	{
		this->_shape.radius = radius;
		this->update_shape();
	}

	void CapsuleColliderComponent::set_height(float height)
	{
		this->_shape.height = height;
		this->update_shape();
	}

	void CapsuleColliderComponent::set_axis(ShapeAxis axis)
	{
		this->_shape.axis = axis;
		this->update_shape();
	}

	void CapsuleColliderComponent::set_shape(Shape shape)
	{
		this->_shape = shape;
		this->update_shape();
	}

	void CapsuleColliderComponent::on_update_collider_transform()
	{
		this->get_world().get_system<PhysicsSystem>()->set_collider_transform(*this, this->get_collider_transform());
	}

	bool CapsuleColliderComponent::on_activate()
	{
		this->get_world().get_system<PhysicsSystem>()->create_collider(*this, this->get_entity(), this->get_collider_transform(), this->_shape);
		return true;
	}

	void CapsuleColliderComponent::on_deactivate()
	{
		this->get_world().get_system<PhysicsSystem>()->destroy_collider(*this);
	}

	void CapsuleColliderComponent::update_shape()
	{
		if (this->has_spawned() && this->is_activate())
		{
			this->get_world().get_system<PhysicsSystem>()->set_collider_shape(*this, this->_shape);
		}
	}
}
