// Entity.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Engine/Entity.h"
#include "../include/Engine/Components/Physics/ColliderComponent.h"
#include "../include/Engine/World.h"
#include "../include/Engine/Systems/PhysicsSystem.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::Entity)
.Data("Name", &Entity::_name)
.Data("Components", &Entity::_components, DF_Transient)
.Data("Transform", &Entity::_transform)
.Data("Parent", &Entity::_parent)
.Data("Children", &Entity::_children, DF_Transient)
.Property("Name", &Entity::GetName, &Entity::EDITOR_SetName, "The name of this Entity", PF_EditorOnly);

BUILD_ENUM_REFLECTION(Willow::Entity::PhysicsMode)
.Value("Transient", Willow::Entity::PhysicsMode::Transient)
.Value("Ghost", Willow::Entity::PhysicsMode::Ghost)
.Value("Kinematic", Willow::Entity::PhysicsMode::Kinematic)
.Value("Dynamic", Willow::Entity::PhysicsMode::Dynamic);

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	Entity::Entity()
		: _physicsMode{ PhysicsMode::Transient }
	{
		_parent = nullptr;
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
		switch (_physicsMode)
		{
		case PhysicsMode::Transient:
			writer.PushValue("PhysicsMode", "Transient");
			break;
		case PhysicsMode::Ghost:
			writer.PushValue("PhysicsMode", "Ghost");
			break;
		case PhysicsMode::Kinematic:
			writer.PushValue("PhysicsMode", "Kinematic");
			break;
		case PhysicsMode::Dynamic:
			writer.PushValue("PhsyicsMode", "Dynamic");
			break;
		}

		// Serialize physics state
		writer.AddChild("PhysicsState", [this](ArchiveWriter& child)
		{
			child.PushValue("Mass", this->GetMass());
			child.PushValue("LinearMotionFactor", this->GetLinearMotionFactor());
			child.PushValue("AngularMotionFactor", this->GetAngularMotionFactor());
			child.PushValue("Friction", this->GetFriction());
			child.PushValue("RollingFriction", this->GetRollingFriction());
		});
	}

	void Entity::FromArchive(const ArchiveReader& reader)
	{
		Base::FromArchive(reader);

		if (_parent)
		{
			_parent->_children.Add(this);
		}

		// Deserialize physics mode
		reader.GetChild("PhysicsMode", [this](const ArchiveReader& child)
		{
			String value;
			child.GetValue(value);

			if (value == "Transient")
			{
				this->SetPhysicsMode(PhysicsMode::Transient);
			}
			else if (value == "Ghost")
			{
				this->SetPhysicsMode(PhysicsMode::Ghost);
			}
			else if (value == "Kinematic")
			{
				this->SetPhysicsMode(PhysicsMode::Kinematic);
			}
			else if (value == "Dynamic")
			{
				this->SetPhysicsMode(PhysicsMode::Dynamic);
			}
		});

		// Deserialize physics state
		reader.GetChild("PhysicsState", [this](const ArchiveReader& child)
		{
			child.PullValue("Mass", this->_physicsState.Mass);
			child.PullValue("LinearMotionFactor", this->_physicsState.LinearMotionFactor);
			child.PullValue("AngularMotionFactor", this->_physicsState.AngularMotionFactor);
			child.PullValue("Friction", this->_physicsState.Friction);
			child.PullValue("RollingFriction", this->_physicsState.RollingFriction);
		});
	}

	bool Entity::IsActor() const
	{
		return this->GetType() != TypeOf<Entity>();
	}

	Entity* Entity::GetActor()
	{
		if (this->IsActor())
		{
			return this;
		}
		else if (_parent)
		{
			return _parent->GetActor();
		}
		else
		{
			return nullptr;
		}
	}

	const Entity* Entity::GetActor() const
	{
		if (this->IsActor())
		{
			return this;
		}
		else if (_parent)
		{
			return _parent->GetActor();
		}
		else
		{
			return nullptr;
		}
	}

	bool Entity::IsParentedTo(const Entity& entity) const
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

	void Entity::SetParent(Entity* parent, SetParentOffsetMode /*mode*/) // TODO: Handle mode
	{
		if (_parent != nullptr && parent->IsParentedTo(*this))
		{
			// This would create a parent cycle, abort
			Console::Warning("Attempt to parent entity '@' to '@' would create a parent cycle.", this->GetName(), parent->GetName());
			return;
		}

		// If we currently have a parent
		if (_parent)
		{
			_parent->_children.DeleteFirst(this);
		}

		// Assign the parent
		_parent = parent;

		// If we NOW have a parent
		if (_parent)
		{
			_parent->_children.Add(this);
		}
	}

	Vec3 Entity::GetLocation() const
	{
		return _transform.Location;
	}

	Vec3 Entity::GetWorldLocation() const
	{
		if (this->HasParent())
		{
			return this->GetParent()->GetTransformationMatrix() * this->GetLocation();
		}
		else
		{
			return this->GetLocation();
		}
	}

	void Entity::SetLocation(const Vec3& location)
	{
		_transform.Location = location;
		this->UpdatePhysicsTransform();
	}

	void Entity::SetWorldLocation(const Vec3& location)
	{
		// TODO
		this->SetLocation(location);
	}

	void Entity::Translate(const Vec3& vec)
	{
		Vec3 newVec = Mat4::Rotate(this->GetWorldRotation()) * vec;
		_transform.Location = _transform.Location + newVec;
		this->UpdatePhysicsTransform();
	}

	void Entity::TranslateGlobal(const Vec3&)
	{
		// TODO
	}

	Quat Entity::GetRotation() const
	{
		return _transform.Rotation;
	}

	Quat Entity::GetWorldRotation() const
	{
		if (this->HasParent())
		{
			return this->GetParent()->GetWorldRotation() * _transform.Rotation;
		}
		else
		{
			return _transform.Rotation;
		}
	}

	void Entity::SetRotation(const Quat&)
	{
		// TODO
	}

	void Entity::SetWorldRotation(const Quat& rot)
	{
		// TODO
		_transform.Rotation = rot;
		this->UpdatePhysicsTransform();
	}

	void Entity::Rotate(const Vec3& axis, Angle angle)
	{
		_transform.Rotation.RotateByAxisAngle(axis, angle, true);
		this->UpdatePhysicsTransform();
	}

	void Entity::RotateGlobal(const Vec3& axis, Angle angle)
	{
		_transform.Rotation.RotateByAxisAngle(axis, angle, false);
		this->UpdatePhysicsTransform();
	}

	Vec3 Entity::GetScale() const
	{
		return _transform.Scale;
	}

	void Entity::SetScale(const Vec3& scale)
	{
		_transform.Scale = scale;
		this->UpdatePhysicsTransform();
	}

	void Entity::Scale(const Vec3& vec)
	{
		_transform.Scale = _transform.Scale + vec;
		this->UpdatePhysicsTransform();
	}

	Mat4 Entity::GetTransformationMatrix() const
	{
		if (this->HasParent())
		{
			return this->GetParent()->GetTransformationMatrix() *
				Mat4::Translate(this->GetLocation()) *
				Mat4::Rotate(this->GetRotation()) *
				Mat4::Scale(this->GetScale());
		}
		else
		{
			return 	Mat4::Translate(this->GetLocation()) *
				Mat4::Rotate(this->GetRotation()) *
				Mat4::Scale(this->GetScale());
		}
	}

	void Entity::SetPhysicsMode(PhysicsMode mode)
	{
		// If we're already in this mode
		if (this->GetPhysicsMode() == mode)
		{
			return;
		}

		_physicsMode = mode;

		// If the object hasn't spawned yet
		if (this->GetState() == State::Uninitialized)
		{
			// Initialize it later
			return;
		}

		this->UpdatePhysicsMode();
	}

	void Entity::SetMass(float mass)
	{
		_physicsState.Mass = mass;
		this->UpdatePhysicsState();
	}

	void Entity::SetRollingFriction(float rollingFriction)
	{
		_physicsState.RollingFriction = rollingFriction;
		this->UpdatePhysicsState();
	}

	Vec3 Entity::GetLinearVelocity() const
	{
		Vec3 linearVelocity;
		this->GetWorld().GetSystem<PhysicsSystem>()->GetEntityLinearVelocity(linearVelocity, *this);
		return linearVelocity;
	}

	void Entity::SetLinearVelocity(const Vec3& linearVelocity)
	{
		this->GetWorld().GetSystem<PhysicsSystem>()->SetEntityLinearVelocity(*this, linearVelocity);
	}

	Vec3 Entity::GetAngularVelocity() const
	{
		Vec3 angularVelocity;
		this->GetWorld().GetSystem<PhysicsSystem>()->GetEntityAngularVelocity(angularVelocity, *this);
		return angularVelocity;
	}

	void Entity::SetAngularVelocity(const Vec3& angularVelocity)
	{
		this->GetWorld().GetSystem<PhysicsSystem>()->SetEntityAngularVelocity(*this, angularVelocity);
	}

	void Entity::ApplyForce(const Vec3& force, const Vec3& offset)
	{
		this->GetWorld().GetSystem<PhysicsSystem>()->ApplyForce(*this, force, offset);
	}

	void Entity::ApplyImpulse(const Vec3& impulse, const Vec3& offset)
	{
		this->GetWorld().GetSystem<PhysicsSystem>()->ApplyImpulse(*this, impulse, offset);
	}

	void Entity::ApplyTorque(const Vec3& torque)
	{
		this->GetWorld().GetSystem<PhysicsSystem>()->ApplyTorque(*this, torque);
	}

	void Entity::ApplyTorqueImpulse(const Vec3& torque)
	{
		this->GetWorld().GetSystem<PhysicsSystem>()->ApplyTorqueImpulse(*this, torque);
	}

	void Entity::SetLinearMotionFactor(const Vec3& factor)
	{
		_physicsState.LinearMotionFactor = factor;
		this->UpdatePhysicsState();
	}

	void Entity::SetAngularMotionFactor(const Vec3& factor)
	{
		_physicsState.AngularMotionFactor = factor;
		this->UpdatePhysicsState();
	}

	void Entity::SetFriction(float friction)
	{
		_physicsState.Friction = friction;
		this->UpdatePhysicsState();
	}

	void Entity::OnSpawn()
	{
		if (auto phys = this->GetWorld().GetSystem<PhysicsSystem>())
		{
			phys->CreateEntity(*this, this->GetParent(), _transform, _physicsMode, _physicsState);
		}
	}

	void Entity::OnDestroy()
	{
		for (auto child : _children)
		{
			child->Destroy();
		}

		for (auto component : _components)
		{
			component->Destroy();
		}

		if (auto phys = this->GetWorld().GetSystem<PhysicsSystem>())
		{
			phys->DestroyEntity(*this);
		}
	}

	void Entity::EDITOR_SetName(String name)
	{
		_name = std::move(name);
	}

	void Entity::UpdatePhysicsMode()
	{
		if (auto phys = this->GetWorld().GetSystem<PhysicsSystem>())
		{
			phys->SetEntityPhysicsMode(*this, _physicsMode);
		}
	}

	void Entity::UpdatePhysicsState()
	{
		if (auto phys = this->GetWorld().GetSystem<PhysicsSystem>())
		{
			phys->SetEntityPhysicsState(*this, _physicsState);
		}
	}

	void Entity::UpdatePhysicsTransform()
	{
		if (auto phys = this->GetWorld().GetSystem<PhysicsSystem>())
		{
			phys->UpdateEntityTransform(*this);
		}
	}
}
