// SphereColliderComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Engine/Components/Physics/SphereColliderComponent.h"
#include "../../../include/Engine/World.h"
#include "../../../include/Engine/Systems/PhysicsSystem.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::SphereColliderComponent)
.Property("radius", &SphereColliderComponent::get_radius, &SphereColliderComponent::set_radius, "", "Sphere");

namespace willow
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
		writer.PushValue("radius", this->get_radius());
	}

	void SphereColliderComponent::FromArchive(const ArchiveReader& reader)
	{
		this->Base::FromArchive(reader);
		reader.PullValue("radius", this->_shape.radius);
		this->update_shape();
	}

	void SphereColliderComponent::set_radius(float radius)
	{
		this->_shape.radius = radius;
		this->update_shape();
	}

	void SphereColliderComponent::on_update_collider_transform()
	{
		this->get_world().get_system<PhysicsSystem>()->set_collider_transform(*this, this->get_collider_transform());
	}

	bool SphereColliderComponent::on_activate()
	{
		this->get_world().get_system<PhysicsSystem>()->create_collider(*this, this->get_entity(), this->get_collider_transform(), this->_shape);
		return true;
	}

	void SphereColliderComponent::on_deactivate()
	{
		this->get_world().get_system<PhysicsSystem>()->destroy_collider(*this);
	}

	void SphereColliderComponent::update_shape()
	{
		if (this->has_spawned() && this->is_activate())
		{
			this->get_world().get_system<PhysicsSystem>()->set_collider_shape(*this, this->_shape);
		}
	}
}
