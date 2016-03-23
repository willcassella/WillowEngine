// Entity.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include "../include/Engine/Entity.h"
#include "../include/Engine/Components/Physics/ColliderComponent.h"
#include "../include/Engine/World.h"
#include "Physics/PhysicsWorld.h"
#include "Physics/PhysicsBody.h"
#include "Physics/EntityCollider.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::Entity)
.Data("Name", &Entity::_name)
.Data("World", &Entity::_world)
.Data("Components", &Entity::_components, DF_Transient)
.Data("Transform", &Entity::_transform)
.Data("Parent", &Entity::_parent)
.Data("Children", &Entity::_children, DF_Transient)
.Data("Mass", &Entity::_cachedMass)
.Property("Name", &Entity::GetName, &Entity::EDITOR_SetName, "The name of this Entity", PF_EditorOnly);

BUILD_ENUM_REFLECTION(Willow::Entity::PhysicsMode)
.Value("Transient", Willow::Entity::PhysicsMode::Transient)
.Value("Sensor", Willow::Entity::PhysicsMode::Sensor)
.Value("Kinematic", Willow::Entity::PhysicsMode::Kinematic)
.Value("Dynamic", Willow::Entity::PhysicsMode::Dynamic);

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	Entity::Entity()
		: _collider{ std::make_unique<EntityCollider>() }
	{
		_world = nullptr;
		_parent = nullptr;
	}

	Entity::~Entity()
	{
		// All done
	}

	///////////////////
	///   Methods   ///

	void Entity::FromArchive(const ArchiveReader& reader)
	{
		Base::FromArchive(reader);

		if (_parent)
		{
			_parent->_children.Add(this);
		}
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
		return _transform.GetLocation();
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
		_transform.SetLocation(location);
	}

	void Entity::SetWorldLocation(const Vec3& location)
	{
		// TODO
		this->SetLocation(location);
	}

	void Entity::Translate(const Vec3& vec)
	{
		Vec3 newVec = Mat4::Rotate(this->GetWorldRotation()) * vec;
		_transform.SetLocation(_transform.GetLocation() + newVec);
	}

	void Entity::TranslateGlobal(const Vec3&)
	{
		// TODO
	}

	Quat Entity::GetRotation() const
	{
		return _transform.GetRotation();
	}

	Quat Entity::GetWorldRotation() const
	{
		if (this->HasParent())
		{
			return this->GetParent()->GetWorldRotation() * _transform.GetRotation();
		}
		else
		{
			return _transform.GetRotation();
		}
	}

	void Entity::SetRotation(const Quat&)
	{
		// TODO
	}

	void Entity::SetWorldRotation(const Quat& rot)
	{
		// TODO
		_transform.SetRotation(rot);
	}

	void Entity::Rotate(const Vec3& axis, Angle angle)
	{
		auto rotation = _transform.GetRotation();
		rotation.RotateByAxisAngle(axis, angle, true);
		_transform.SetRotation(rotation);
	}

	void Entity::RotateGlobal(const Vec3& axis, Angle angle)
	{
		auto rotation = _transform.GetRotation();
		rotation.RotateByAxisAngle(axis, angle, false);
		_transform.SetRotation(rotation);
	}

	Vec3 Entity::GetScale() const
	{
		return _transform.GetScale();
	}

	void Entity::SetScale(const Vec3& scale)
	{
		_transform.SetScale(scale);
	}

	void Entity::Scale(const Vec3& vec)
	{
		auto newScale = _transform.GetScale() + vec;
		_transform.SetScale(newScale);
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

	Entity::PhysicsMode Entity::GetPhysicsMode() const
	{
		return _physicsMode;
	}

	void Entity::SetPhysicsMode(PhysicsMode mode)
	{
		// If we're already in this mode
		if (this->GetPhysicsMode() == mode)
		{
			return;
		}

		// If the object hasn't spawned yet
		if (this->GetState() == State::Uninitialized)
		{
			// Set the mode, initialize it later
			_physicsMode = mode;
			return;
		}

		// If we're kinematic and we want to be dynamic
		if (this->GetPhysicsMode() == PhysicsMode::Kinematic && mode == PhysicsMode::Dynamic)
		{
			_physicsMode = mode;

			// Calculate inertia
			btVector3 inertia;
			_collider->calculateLocalInertia(_cachedMass, inertia);
			static_cast<btRigidBody*>(_physicsBody->Body.get())->setMassProps(_cachedMass, inertia);

			// Disable kinematic flag
			_physicsBody->Body->setCollisionFlags(_physicsBody->Body->getCollisionFlags() & ~btCollisionObject::CF_KINEMATIC_OBJECT);

			// Set normal activation
			_physicsBody->Body->setActivationState(ACTIVE_TAG);
			return;
		}

		// If we're dynamic and we want to be kinematic
		if (this->GetPhysicsMode() == PhysicsMode::Dynamic && mode == PhysicsMode::Kinematic)
		{
			_physicsMode = mode;
			
			// Set mass and inertia to '0'
			static_cast<btRigidBody*>(_physicsBody->Body.get())->setMassProps(0, { 0, 0, 0 });
			
			// Add kinematic flag 
			_physicsBody->Body->setCollisionFlags(_physicsBody->Body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
			
			// Diable deactivation
			_physicsBody->Body->setActivationState(DISABLE_DEACTIVATION);
			return;
		}

		// Change is more complex, destroy and rebuild physics state
		this->DestroyPhysics();
		_physicsMode = mode;
		this->InitializePhysics();
	}

	float Entity::GetMass() const
	{
		return _cachedMass;
	}

	void Entity::SetMass(float mass)
	{
		_cachedMass = mass;
		this->INTERNAL_UpdateInertia();
	}

	void Entity::INTERNAL_UpdateInertia()
	{
		if (this->GetPhysicsMode() == PhysicsMode::Dynamic)
		{
			btVector3 inertia;
			_collider->calculateLocalInertia(_cachedMass, inertia);
			static_cast<btRigidBody*>(_physicsBody->Body.get())->setMassProps(_cachedMass, inertia);
		}

		if (_parent)
		{
			_parent->INTERNAL_UpdateInertia();
		}
	}

	EntityCollider* Entity::INTERNAL_GetCollider()
	{
		return _collider.get();
	}

	const EntityCollider* Entity::INTERNAL_GetCollider() const
	{
		return _collider.get();
	}

	void Entity::ApplyForce(const Vec3& force, const Vec3& offset)
	{
		if (this->GetPhysicsMode() == PhysicsMode::Dynamic)
		{
			auto body = static_cast<btRigidBody*>(_physicsBody->Body.get());
			body->setActivationState(ACTIVE_TAG);
			body->applyForce(ConvertToBullet(force), ConvertToBullet(offset));
		}
	}

	void Entity::ApplyImpulse(const Vec3& impulse, const Vec3& offset)
	{
		if (this->GetPhysicsMode() == PhysicsMode::Dynamic)
		{
			auto body = static_cast<btRigidBody*>(_physicsBody->Body.get());
			body->setActivationState(ACTIVE_TAG);
			body->applyImpulse(ConvertToBullet(impulse), ConvertToBullet(offset));
		}
	}

	void Entity::ApplyTorque(const Vec3& torque)
	{
		if (this->GetPhysicsMode() == PhysicsMode::Dynamic)
		{
			auto body = static_cast<btRigidBody*>(_physicsBody->Body.get());
			body->setActivationState(ACTIVE_TAG);
			body->applyTorque(ConvertToBullet(torque));
		}
	}

	void Entity::ApplyTorqueImpulse(const Vec3& torque)
	{
		if (this->GetPhysicsMode() == PhysicsMode::Dynamic)
		{
			auto body = static_cast<btRigidBody*>(_physicsBody->Body.get());
			body->setActivationState(ACTIVE_TAG);
			body->applyTorqueImpulse(ConvertToBullet(torque));
		}
	}

	void Entity::OnSpawn()
	{
		if (_physicsBody == nullptr)
		{
			this->InitializePhysics();
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

		this->DestroyPhysics();
	}

	void Entity::EDITOR_SetName(String name)
	{
		_name = std::move(name);
	}

	void Entity::InitializePhysics()
	{
		// If the physics mode is transient, we don't have to do anything
		if (_physicsMode == PhysicsMode::Transient)
		{
			return;
		}

		// Create physics state
		_physicsBody = std::make_unique<PhysicsBody>(*this);

		// If this object is a sensor
		if (_physicsMode == PhysicsMode::Sensor)
		{
			// Create ghost object
			_physicsBody->Body = std::make_unique<btGhostObject>();
			_physicsBody->Body->setCollisionShape(_collider.get());
			
			// Add it to the world
			this->GetWorld().INTERNAL_GetPhysicsWorld().GetDynamicsWorld().addCollisionObject(_physicsBody->Body.get());
		}
		// Otherwise, it must be Kinematic or Dynamic
		else
		{	
			float mass = 0;
			btVector3 inertia{ 0, 0, 0 };

			// If it's a dynamic object, we need to calculate mass and inertia
			if (_physicsMode == PhysicsMode::Dynamic)
			{
				mass = _cachedMass;
				_collider->calculateLocalInertia(mass, inertia);
			}

			// Create a btRigidBody
			auto rigidBody = std::make_unique<btRigidBody>(mass, _physicsBody.get(), _collider.get(), inertia);

			// If it's kinematic, set Kinematic flag
			if (_physicsMode == PhysicsMode::Kinematic)
			{
				rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
				rigidBody->setActivationState(DISABLE_DEACTIVATION);
			}

			// Add it to the world
			this->GetWorld().INTERNAL_GetPhysicsWorld().GetDynamicsWorld().addRigidBody(rigidBody.get());

			// Add it to the physics state
			_physicsBody->Body = std::move(rigidBody);
		}
	}

	void Entity::DestroyPhysics()
	{
		if (_physicsMode == PhysicsMode::Transient)
		{
			// We don't have to do anything
			return;
		}

		if (_physicsMode == PhysicsMode::Sensor)
		{
			// Remove it as a normal CollisionObject
			this->GetWorld().INTERNAL_GetPhysicsWorld().GetDynamicsWorld().removeCollisionObject(_physicsBody->Body.get());
		}
		else
		{
			this->GetWorld().INTERNAL_GetPhysicsWorld().GetDynamicsWorld().removeRigidBody(static_cast<btRigidBody*>(_physicsBody->Body.get()));
		}

		// Object no longer participates in simulation
		_physicsBody = nullptr;
		_physicsMode = PhysicsMode::Transient;
	}
}
