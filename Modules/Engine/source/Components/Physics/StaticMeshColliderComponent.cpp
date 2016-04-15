// StaticMeshColliderComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Engine/Components/Physics/StaticMeshColliderComponent.h"
#include "../../../include/Engine/World.h"
#include "../../../include/Engine/Systems/PhysicsSystem.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::StaticMeshColliderComponent)
.Property("mesh", &StaticMeshColliderComponent::get_mesh, &StaticMeshColliderComponent::set_mesh);

namespace willow
{
	////////////////////////
	///   Constructors   ///

	StaticMeshColliderComponent::StaticMeshColliderComponent()
	{
		// All done
	}

	StaticMeshColliderComponent::~StaticMeshColliderComponent()
	{
		// All done
	}

	///////////////////
	///   Methods   ///

	void StaticMeshColliderComponent::ToArchive(ArchiveWriter& writer) const
	{
		this->Base::ToArchive(writer);
		writer.PushValue("mesh", this->_shape.mesh);
	}

	void StaticMeshColliderComponent::FromArchive(const ArchiveReader& reader)
	{
		this->Base::FromArchive(reader);
		reader.PullValue("mesh", this->_shape.mesh);
		this->update_shape();
	}

	void StaticMeshColliderComponent::set_mesh(ResourceHandle<StaticMesh> mesh)
	{
		this->_shape.mesh = mesh;
		this->update_shape();
	}

	void StaticMeshColliderComponent::set_shape(Shape shape)
	{
		this->_shape = shape;
		this->update_shape();
	}

	void StaticMeshColliderComponent::on_update_collider_transform()
	{
		this->get_world().get_system<PhysicsSystem>()->set_collider_transform(*this, this->get_collider_transform());
	}

	bool StaticMeshColliderComponent::on_activate()
	{
		if (this->_shape.mesh)
		{
			this->get_world().get_system<PhysicsSystem>()->create_collider(*this, this->get_entity(), this->get_collider_transform(), this->_shape);
			return true;
		}
		else
		{
			return false;
		}
	}

	void StaticMeshColliderComponent::on_deactivate()
	{
		this->get_world().get_system<PhysicsSystem>()->destroy_collider(*this);
	}

	void StaticMeshColliderComponent::update_shape()
	{
		if (this->is_initialized())
		{
			this->get_world().get_system<PhysicsSystem>()->set_collider_shape(*this, this->_shape);
		}
	}
}
