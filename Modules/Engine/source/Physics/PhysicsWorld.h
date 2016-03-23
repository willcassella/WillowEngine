// PhysicsWorld.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Physics.h"

namespace Willow
{
	/** Manages World Bullet physics state. */
	class PhysicsWorld final
	{
		////////////////////////
		///   Constructors   ///
	public:

		PhysicsWorld()
		{
			// Initialize physics configuration
			_broadPhaseInterface = std::make_unique<btDbvtBroadphase>();
			_collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
			_dispatcher = std::make_unique<btCollisionDispatcher>(_collisionConfiguration.get());
			btGImpactCollisionAlgorithm::registerAlgorithm(_dispatcher.get());

			// Initialize the physics world
			_dynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(_dispatcher.get(), _broadPhaseInterface.get(), _constraintSolver.get(), _collisionConfiguration.get());
			_dynamicsWorld->setGravity(btVector3{ 0, -10, 0 });
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
}
