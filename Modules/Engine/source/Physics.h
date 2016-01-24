// BulletIntegration.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <memory>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include "../include/Engine/Components/PhysicalComponent.h"

/////////////////
///   Types   ///

/** Structure managing global Bullet physics data. */
struct PhysicsWorld final
{
	////////////////////////
	///   Constructors   ///
public:

	PhysicsWorld()
	{
		// Spawn physics configuration
		_broadPhaseInterface = std::make_unique<btDbvtBroadphase>();
		_collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
		_dispatcher = std::make_unique<btCollisionDispatcher>(_collisionConfiguration.get());
		btGImpactCollisionAlgorithm::registerAlgorithm(_dispatcher.get());

		// Spawn the physics world
		_dynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(_dispatcher.get(), _broadPhaseInterface.get(), _constraintSolver.get(), _collisionConfiguration.get());
		_dynamicsWorld->setGravity(btVector3(0, -10, 0));
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the dynamics world. */
	btDynamicsWorld& GetDynamicsWorld()
	{
		return *_dynamicsWorld;
	}

	/** Returns the dynamics world. */
	const btDynamicsWorld& GetDynamicsWorld() const
	{
		return *_dynamicsWorld;
	}

	////////////////
	///   Data   ///
private:

	// Physics configuration
	std::unique_ptr<btBroadphaseInterface> _broadPhaseInterface;
	std::unique_ptr<btCollisionConfiguration> _collisionConfiguration;
	std::unique_ptr<btCollisionDispatcher> _dispatcher;
	std::unique_ptr<btConstraintSolver> _constraintSolver;

	// Physics world
	std::unique_ptr<btDynamicsWorld> _dynamicsWorld;
};

/** Represents a physical body in the Bullet simulation world */
class PhysicsState final : public btMotionState
{
	////////////////////////
	///   Constructors   ///
public:

	PhysicsState(PhysicalComponent& owner)
		: _owner(&owner)
	{
		// All done
	}

	//////////////////
	///   Fields   ///
public:

	std::unique_ptr<btCollisionObject> Body;

	///////////////////
	///   Methods   ///
public:

	void getWorldTransform(btTransform& worldTransform) const override
	{
		// Set the world location
		Vec3 wLocation = _owner->GetWorldLocation();
		btVector3 btLocation = { wLocation.X, wLocation.Y, wLocation.Z };
		worldTransform.setOrigin(btLocation);

		// Set the world rotation
		Quat wRotation = _owner->GetWorldRotation();
		btQuaternion btRotation = { wRotation.X, wRotation.Y, wRotation.Z, wRotation.W };
		worldTransform.setRotation(btRotation);
	}

	void setWorldTransform(const btTransform& worldTransform) override
	{
		Vec3 location = { worldTransform.getOrigin().getX(), worldTransform.getOrigin().getY(), worldTransform.getOrigin().getZ() };
		_owner->SetLocation(location);
	}

	////////////////
	///   Data   ///
private:

	PhysicalComponent* _owner;
};
