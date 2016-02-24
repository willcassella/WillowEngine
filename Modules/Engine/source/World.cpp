// World.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Engine/World.h"
#include "../include/Engine/ServiceInterfaces/IRenderer.h"
#include "Physics.h"

static_assert(std::is_same<Scalar, btScalar>::value, "The engine is not configured to use the same Scalar type as Bullet.");

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::World)
.Data("GameObjects", &World::_gameObjects)
.Data("Entities", &World::_entities)
.Data("Components", &World::_components)
.Data("Destroyed", &World::_destroyedObjects, DF_Transient)
.Data("NextGameObjectID", &World::_nextGameObjectID)
.Field("Events", &World::Events)
.Field("TimeDilation", &World::TimeDilation, "The time dilation of the world. Default is 1.")
.Field("TimeStep", &World::TimeStep, "The amount of time (ms) that each update of the world represents.");

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	World::World()
	{
		_physicsWorld = std::make_unique<PhysicsWorld>();
		_nextGameObjectID = 1;
	}

	World::~World()
	{
		// Do nothing
	}

	///////////////////
	///   Methods   ///

	void World::Update()
	{
		Events.DispatchEvent("Update", this->TimeDilation);
		Events.Flush();

		// Remove stale objects
		while (!_destroyedObjects.IsEmpty())
		{
			auto object = _destroyedObjects.Pop();
			_gameObjects.Remove(object->GetID());
		}

		// Simulate physics
		_physicsWorld->GetDynamicsWorld().stepSimulation(TimeStep, 10);
	}
}
