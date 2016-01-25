// PhysicalComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include "../../include/Engine/Components/PhysicalComponent.h"
#include "../../include/Engine/World.h"
#include "../Physics.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(PhysicalComponent)
.Property("Mass", &PhysicalComponent::GetMass, &PhysicalComponent::SetMass, "The mass of this object.");

BUILD_ENUM_REFLECTION(PhysicsMode);

////////////////////////
///   Constructors   ///

PhysicalComponent::PhysicalComponent()
{
	_physicsState = std::make_unique<PhysicsState>(*this);
}

PhysicalComponent::~PhysicalComponent()
{
	DestroyPhysics();
}

///////////////////
///   Methods   ///

void PhysicalComponent::SetMass(Scalar)
{
	// TODO
}

void PhysicalComponent::SetPhysicsMode(PhysicsMode mode)
{
	// If we are already in this mode
	if (mode == _physicsMode)
	{
		return;
	}

	if (_physicsState->Body != nullptr)
	{
		DestroyPhysics();
	}

	_physicsMode = mode;
	SetupPhysics();
}

void PhysicalComponent::OnSpawn()
{
	Base::OnSpawn();
	SetupPhysics();
}

void PhysicalComponent::SetupPhysics()
{
	// If the current physics mode is to have no physics
	if (GetPhysicsMode() == PhysicsMode::Transient)
	{
		return;
	}

	auto* shape = this->GetShape();
	
	if (GetPhysicsMode() == PhysicsMode::Ghost)
	{
		_physicsState->Body = std::make_unique<btGhostObject>();
		_physicsState->Body->setCollisionShape(shape);
		GetWorld().GetPhysicsWorld().GetDynamicsWorld().addCollisionObject(_physicsState->Body.get());
	}
	else
	{
		btVector3 localInertia;
		shape->calculateLocalInertia(this->GetMass(), localInertia);

		_physicsState->Body = std::make_unique<btRigidBody>(this->GetMass(), _physicsState.get(), shape, localInertia);
		GetWorld().GetPhysicsWorld().GetDynamicsWorld().addRigidBody(static_cast<btRigidBody*>(_physicsState->Body.get()));
	}

	if (GetPhysicsMode() == PhysicsMode::Kinematic)
	{
		_physicsState->Body->setCollisionFlags(_physicsState->Body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	}
}

void PhysicalComponent::DestroyPhysics()
{
	if (GetPhysicsMode() == PhysicsMode::Transient)
	{
		return;
	}
	else if (GetPhysicsMode() == PhysicsMode::Ghost)
	{
		GetWorld().GetPhysicsWorld().GetDynamicsWorld().removeCollisionObject(_physicsState->Body.get());
	}
	else
	{
		GetWorld().GetPhysicsWorld().GetDynamicsWorld().removeRigidBody(static_cast<btRigidBody*>(_physicsState->Body.get()));
		_physicsState->Body = nullptr;
	}
}
