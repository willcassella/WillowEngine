// ColliderComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Engine/Components/Physics/ColliderComponent.h"
#include "../../../include/Engine/World.h"
#include "../../../include/Engine/Systems/PhysicsSystem.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::ColliderComponent)
.Data("is_activate", &ColliderComponent::_is_active)
.Data("collider_transform", &ColliderComponent::_collider_transform)
.Property("is_activate", &ColliderComponent::is_activate, &ColliderComponent::EDITOR_set_active, "", "Collider", PF_EditorOnly)
.Property("location", &ColliderComponent::get_collider_location, &ColliderComponent::set_collider_location, "", "Collider")
.Property("rotation", &ColliderComponent::get_collider_rotation, &ColliderComponent::set_collider_rotation, "", "Collider")
.Property("scale", &ColliderComponent::get_collider_scale, &ColliderComponent::set_collider_scale, "", "Collider");

BUILD_ENUM_REFLECTION(willow::ColliderComponent::ShapeAxis)
.Value("X", willow::ColliderComponent::ShapeAxis::X)
.Value("Y", willow::ColliderComponent::ShapeAxis::Y)
.Value("Z", willow::ColliderComponent::ShapeAxis::Z);

namespace willow
{
	////////////////////////
	///   Constructors   ///

	ColliderComponent::ColliderComponent()
		: _is_active{ true }
	{
		// All done
	}

	///////////////////
	///   Methods   ///

	void ColliderComponent::activate_collider()
	{
		if (this->is_activate())
		{
			// We're already activated
			return;
		}

		if (!this->has_spawned() || this->is_destroyed())
		{
			// We'll activate once we spawn
			this->_is_active = true;
			return;
		}

		// Attempt to activate
		this->_is_active = this->on_activate();
	}

	void ColliderComponent::deactivate_collider()
	{
		if (!this->is_activate())
		{
			// We're already deactivated
			return;
		}

		if (!this->has_spawned() || this->is_destroyed())
		{
			// We haven't spawned yet, so nothing to undo
			this->_is_active = false;
			return;
		}

		this->on_deactivate();
	}

	void ColliderComponent::set_collider_transform(const Transform& transform)
	{
		this->_collider_transform = transform;
		this->update_collider_transform();
	}

	void ColliderComponent::set_collider_location(const Vec3& location)
	{
		this->_collider_transform.location = location;
		this->update_collider_transform();
	}

	void ColliderComponent::set_collider_rotation(const Quat& rotation)
	{
		this->_collider_transform.rotation = rotation;
		this->update_collider_transform();
	}

	void ColliderComponent::set_collider_scale(const Vec3& scale)
	{
		this->_collider_transform.scale = scale;
		this->update_collider_transform();
	}

	void ColliderComponent::on_initialize()
	{
		this->Base::on_spawn();

		if (this->is_activate())
		{
			this->_is_active = this->on_activate();
		}
	}

	void ColliderComponent::on_destroy()
	{
		this->Base::on_destroy();

		if (this->is_activate())
		{
			this->on_deactivate();
		}
	}

	void ColliderComponent::update_collider_transform()
	{
		if (this->is_activate() && this->has_spawned())
		{
			this->on_update_collider_transform();
		}
	}

	void ColliderComponent::EDITOR_set_active(bool active)
	{
		if (active)
		{
			this->activate_collider();
		}
		else
		{
			this->deactivate_collider();
		}
	}
}
