// World.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Engine/World.h"
#include "../include/Engine/ServiceInterfaces/IRenderer.h"
#include "Physics.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::World)
.Data("GameObjects", &World::_gameObjects, DF_Transient)
.Data("Entities", &World::_entities, DF_Transient)
.Data("Components", &World::_components, DF_Transient)
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
	
	void World::ToArchive(ArchiveWriter& writer) const
	{
		writer.SetID(this);
		writer.PushValue("TimeDilation", this->TimeDilation);
		writer.PushValue("TimeStep", this->TimeStep);
		writer.PushValue("NextID", _nextGameObjectID);
		
		// Save all entites/components
		writer.AddChild("GameObjects", [this](auto& child)
		{
			for (const auto& kv : this->_gameObjects)
			{
				// Push the given value into this archive, wrapping it in a Node containing its type name and address
				child.PushValueWithID(kv.Second->GetType().GetName(), *kv.Second);
			}
		});
	}

	void World::FromArchive(const ArchiveReader& reader)
	{
		reader.MapID(this);
		reader.PullValue("TimeDilation", this->TimeDilation);
		reader.PullValue("TimeStep", this->TimeStep);
		reader.PullValue("NextID", _nextGameObjectID);
		
		// Load all entities/components
		reader.GetChild("GameObjects", [&](auto& child)
		{
			Queue<Owned<GameObject>> unloadedObjects;

			// Do a first pass, instantiate everything
			child.EnumerateChildren([&](auto& gameobject)
			{
				// Find the type of GameObject that this node is referring to
				auto type = Application::FindType(gameobject.GetName());
				
				if (!type || !type->IsCastableTo(TypeOf<GameObject>()))
				{
					// Type isn't a GameObject type, go to next object
					gameobject.MapID(nullptr);
					unloadedObjects.Push(nullptr);
				}
				else
				{
					// Instantiate it
					auto object = StaticPointerCast<GameObject>(DynamicNew(*type));

					// Map the address of the new instantiation to the address in the archive
					gameobject.MapID(object.GetManagedPointer());
					unloadedObjects.Push(std::move(object));
				}
			});

			// Do a second pass, deserialize everything
			child.EnumerateChildren([&](auto& gameobject)
			{
				// If the object is not null, deserialize it
				if (auto object = unloadedObjects.Pop())
				{
					object->FromArchive(gameobject);
					this->SpawnGameObject(std::move(object));
				}
			});
		});	
	}

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

	void World::SpawnGameObject(Owned<GameObject> owner)
	{
		auto& object = *owner;
		
		// Give the object an ID
		assert(object._state == GameObject::State::Uninitialized);
		object._id = _nextGameObjectID++;
		
		// Add it to the world
		_gameObjects[object.GetID()] = std::move(owner);
		
		if (auto entity = Cast<Entity>(object))
		{
			_entities[object.GetID()] = entity;
		}
		else if (auto component = Cast<Component>(object))
		{
			_components[object.GetID()] = component;
		}

		// Spawn it
		object.OnSpawn();
		object._state = GameObject::State::Spawned;
	}
}
