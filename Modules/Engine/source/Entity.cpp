// Entity.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Engine/Entity.h"
#include "../include/Engine/Components/Physics/ColliderComponent.h"
#include "../include/Engine/World.h"
#include "../include/Engine/Systems/PhysicsSystem.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::Entity)
.Data("name", &Entity::_name)
.Data("components", &Entity::_components, DF_Transient)
.Data("transform", &Entity::_transform)
.Data("parent", &Entity::_parent)
.Data("children", &Entity::_children, DF_Transient)
.Property("name", &Entity::get_name, &Entity::EDITOR_set_name, "The name of this Entity", PF_EditorOnly);

BUILD_ENUM_REFLECTION(willow::Entity::PhysicsMode)
.Value("Transient", willow::Entity::PhysicsMode::Transient)
.Value("Ghost", willow::Entity::PhysicsMode::Ghost)
.Value("Kinematic", willow::Entity::PhysicsMode::Kinematic)
.Value("Dynamic", willow::Entity::PhysicsMode::Dynamic);

namespace willow
{
	////////////////////////
	///   Constructors   ///

	Entity::Entity()
		: _parent{ nullptr }, _physics_mode{ PhysicsMode::Transient }
	{
		// All done
	}

	Entity::~Entity()
	{
		// All done
	}

	///////////////////
	///   Methods   ///

	void Entity::ToArchive(ArchiveWriter& writer) const
	{
		Base::ToArchive(writer);

		// Serialize physics mode
		switch (this->_physics_mode)
		{
		case PhysicsMode::Transient:
			writer.PushValue("physics_mode", "Transient");
			break;
		case PhysicsMode::Ghost:
			writer.PushValue("physics_mode", "Ghost");
			break;
		case PhysicsMode::Kinematic:
			writer.PushValue("physics_mode", "Kinematic");
			break;
		case PhysicsMode::Dynamic:
			writer.PushValue("physics_mode", "Dynamic");
			break;
		}

		// Serialize physics state
		writer.AddChild("physics_state", [this](ArchiveWriter& child)
		{
			child.PushValue("mass", this->get_mass());
			child.PushValue("linear_motion_factor", this->get_linear_motion_factor());
			child.PushValue("angular_motion_factor", this->get_angular_motion_factor());
			child.PushValue("friction", this->get_friction());
			child.PushValue("rolling_friction", this->get_rolling_friction());
		});
	}

	void Entity::FromArchive(const ArchiveReader& reader)
	{
		Base::FromArchive(reader);

		if (this->_parent)
		{
			this->_parent->_children.Add(this);
		}

		// Deserialize physics mode
		reader.GetChild("physics_mode", [this](const ArchiveReader& child)
		{
			String value;
			child.GetValue(value);

			if (value == "Transient")
			{
				this->set_physics_mode(PhysicsMode::Transient);
			}
			else if (value == "Ghost")
			{
				this->set_physics_mode(PhysicsMode::Ghost);
			}
			else if (value == "Kinematic")
			{
				this->set_physics_mode(PhysicsMode::Kinematic);
			}
			else if (value == "Dynamic")
			{
				this->set_physics_mode(PhysicsMode::Dynamic);
			}
		});

		// Deserialize physics state
		reader.GetChild("physics_state", [this](const ArchiveReader& child)
		{
			child.PullValue("mass", this->_physics_state.mass);
			child.PullValue("linear_motion_factor", this->_physics_state.linear_motion_factor);
			child.PullValue("angular_motion_factor", this->_physics_state.angular_motion_factor);
			child.PullValue("friction", this->_physics_state.friction);
			child.PullValue("rolling_friction", this->_physics_state.rolling_friction);
		});
	}

	bool Entity::is_actor() const
	{
		return this->GetType() != TypeOf<Entity>();
	}

	Entity* Entity::get_actor()
	{
		if (this->is_actor())
		{
			return this;
		}
		else if (this->_parent)
		{
			return this->_parent->get_actor();
		}
		else
		{
			return nullptr;
		}
	}

	const Entity* Entity::get_actor() const
	{
		if (this->is_actor())
		{
			return this;
		}
		else if (this->_parent)
		{
			return this->_parent->get_actor();
		}
		else
		{
			return nullptr;
		}
	}

	bool Entity::is_parented_to(const Entity& entity) const
	{
		for (auto ent = this; ent != nullptr; ent = ent->_parent)
		{
			if (ent == &entity)
			{
				return true;
			}
		}

		return false;
	}

	void Entity::set_parent(Entity* parent, SetParentOffsetMode /*mode*/) // TODO: Handle mode
	{
		if (parent && parent->is_parented_to(*this))
		{
			// This would create a parent cycle, abort
			Console::Warning("Attempt to parent entity '@' to '@' would create a parent cycle.", this->get_name(), parent->get_name());
			return;
		}

		// If we currently have a parent
		if (this->_parent)
		{
			this->_parent->_children.DeleteFirst(this);
		}

		// Assign the parent
		this->_parent = parent;

		// If we NOW have a parent
		if (parent)
		{
			parent->_children.Add(this);
		}
	}

	Vec3 Entity::get_location() const
	{
		return this->_transform.location;
	}

	Vec3 Entity::get_world_location() const
	{
		if (this->has_parent())
		{
			return this->get_parent()->get_transformation_matrix() * this->get_location();
		}
		else
		{
			return this->get_location();
		}
	}

	void Entity::set_location(const Vec3& location)
	{
		this->_transform.location = location;
		this->update_physics_transform();
	}

	void Entity::set_world_location(const Vec3& location)
	{
		// TODO
		this->set_location(location);
	}

	void Entity::translate(const Vec3& vec)
	{
		Vec3 newVec = Mat4::Rotate(this->get_world_rotation()) * vec;
		this->_transform.location = this->_transform.location + newVec;
		this->update_physics_transform();
	}

	void Entity::translate_global(const Vec3&)
	{
		// TODO
	}

	Quat Entity::get_rotation() const
	{
		return this->_transform.rotation;
	}

	Quat Entity::get_world_rotation() const
	{
		if (this->has_parent())
		{
			return this->get_parent()->get_world_rotation() * this->_transform.rotation;
		}
		else
		{
			return this->_transform.rotation;
		}
	}

	void Entity::set_rotation(const Quat&)
	{
		// TODO
	}

	void Entity::set_world_rotation(const Quat& rot)
	{
		// TODO
		this->_transform.rotation = rot;
		this->update_physics_transform();
	}

	void Entity::rotate(const Vec3& axis, Angle angle)
	{
		this->_transform.rotation.RotateByAxisAngle(axis, angle, true);
		this->update_physics_transform();
	}

	void Entity::rotate_global(const Vec3& axis, Angle angle)
	{
		this->_transform.rotation.RotateByAxisAngle(axis, angle, false);
		this->update_physics_transform();
	}

	Vec3 Entity::get_scale() const
	{
		return this->_transform.scale;
	}

	void Entity::set_scale(const Vec3& scale)
	{
		this->_transform.scale = scale;
		this->update_physics_transform();
	}

	void Entity::scale(const Vec3& vec)
	{
		this->_transform.scale = this->_transform.scale + vec;
		this->update_physics_transform();
	}

	Mat4 Entity::get_transformation_matrix() const
	{
		if (this->has_parent())
		{
			return this->get_parent()->get_transformation_matrix() *
				Mat4::Translate(this->get_location()) *
				Mat4::Rotate(this->get_rotation()) *
				Mat4::Scale(this->get_scale());
		}
		else
		{
			return 	Mat4::Translate(this->get_location()) *
				Mat4::Rotate(this->get_rotation()) *
				Mat4::Scale(this->get_scale());
		}
	}

	void Entity::set_physics_mode(PhysicsMode mode)
	{
		// If we're already in this mode
		if (this->get_physics_mode() == mode)
		{
			return;
		}

		this->_physics_mode = mode;

		// If the object hasn't spawned yet
		if (this->get_state() == State::Uninitialized)
		{
			// Initialize it later
			return;
		}

		this->update_physics_mode();
	}

	void Entity::set_mass(float mass)
	{
		this->_physics_state.mass = mass;
		this->update_physics_state();
	}

	void Entity::set_rolling_friction(float rollingFriction)
	{
		this->_physics_state.rolling_friction = rollingFriction;
		this->update_physics_state();
	}

	Vec3 Entity::get_linear_velocity() const
	{
		Vec3 linearVelocity;
		this->get_world().get_system<PhysicsSystem>()->get_entity_linear_velocity(linearVelocity, *this);
		return linearVelocity;
	}

	void Entity::set_linear_velocity(const Vec3& linearVelocity)
	{
		this->get_world().get_system<PhysicsSystem>()->set_entity_linear_velocity(*this, linearVelocity);
	}

	Vec3 Entity::get_angular_velocity() const
	{
		Vec3 angularVelocity;
		this->get_world().get_system<PhysicsSystem>()->get_entity_angular_velocity(angularVelocity, *this);
		return angularVelocity;
	}

	void Entity::set_angular_velocity(const Vec3& angularVelocity)
	{
		this->get_world().get_system<PhysicsSystem>()->set_entity_angular_velocity(*this, angularVelocity);
	}

	void Entity::apply_force(const Vec3& force, const Vec3& offset)
	{
		this->get_world().get_system<PhysicsSystem>()->apply_force(*this, force, offset);
	}

	void Entity::apply_impulse(const Vec3& impulse, const Vec3& offset)
	{
		this->get_world().get_system<PhysicsSystem>()->apply_impulse(*this, impulse, offset);
	}

	void Entity::apply_torque(const Vec3& torque)
	{
		this->get_world().get_system<PhysicsSystem>()->apply_torque(*this, torque);
	}

	void Entity::apply_torque_impulse(const Vec3& torque)
	{
		this->get_world().get_system<PhysicsSystem>()->apply_torque_impulse(*this, torque);
	}

	void Entity::set_linear_motion_factor(const Vec3& factor)
	{
		this->_physics_state.linear_motion_factor = factor;
		this->update_physics_state();
	}

	void Entity::set_angular_motion_factor(const Vec3& factor)
	{
		this->_physics_state.angular_motion_factor = factor;
		this->update_physics_state();
	}

	void Entity::set_friction(float friction)
	{
		this->_physics_state.friction = friction;
		this->update_physics_state();
	}

	void Entity::on_initialize()
	{
		this->Base::on_initialize();

		if (auto phys = this->get_world().get_system<PhysicsSystem>())
		{
			phys->create_entity(*this, this->get_parent(), this->_transform, this->_physics_mode, this->_physics_state);
		}
	}

	void Entity::on_destroy()
	{
		this->Base::on_destroy();

		for (auto child : _children)
		{
			child->destroy();
		}

		for (auto component : _components)
		{
			component->destroy();
		}

		if (auto phys = this->get_world().get_system<PhysicsSystem>())
		{
			phys->destroy_entity(*this);
		}
	}

	void Entity::on_collision(Entity& collidee)
	{
		// Do nothing
	}

	void Entity::EDITOR_set_name(String name)
	{
		this->_name = std::move(name);
	}

	void Entity::update_physics_mode()
	{
		if (auto phys = this->get_world().get_system<PhysicsSystem>())
		{
			phys->set_entity_physics_mode(*this, this->_physics_mode);
		}
	}

	void Entity::update_physics_state()
	{
		if (auto phys = this->get_world().get_system<PhysicsSystem>())
		{
			phys->set_entity_physics_state(*this, this->_physics_state);
		}
	}

	void Entity::update_physics_transform()
	{
		if (auto phys = this->get_world().get_system<PhysicsSystem>())
		{
			phys->update_entity_transform(*this);
		}
	}
}
