// World.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Engine/World.h"

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
		_nextGameObjectID = 1;
	}

	World::~World()
	{
		// All done
	}

	///////////////////
	///   Methods   ///
	
	void World::ToArchive(ArchiveWriter& writer) const
	{
		writer.SetRefID(this);
		writer.PushValue("TimeDilation", this->TimeDilation);
		writer.PushValue("TimeStep", this->TimeStep);
		writer.PushValue("NextID", _nextGameObjectID);
		
		// Save all entites/components
		writer.AddChild("GameObjects", [this](auto& child)
		{
			for (const auto& kv : this->_gameObjects)
			{
				// Push the given value into this archive, wrapping it in a Node containing its type name and address
				child.PushReferencedValue(kv.Second->GetType().GetName(), *kv.Second);
			}
		});
	}

	void World::FromArchive(const ArchiveReader& reader)
	{
		reader.MapRefID(this);
		reader.PullValue("TimeDilation", this->TimeDilation);
		reader.PullValue("TimeStep", this->TimeStep);
		reader.PullValue("NextID", _nextGameObjectID);
		
		// Queue of GameObjects that still need to be spawned
		Queue<Owned<GameObject>> unspawnedEntities;
		Queue<Owned<GameObject>> unspawnedComponents;
		
		// Load all entities/components
		reader.GetChild("GameObjects", [&](auto& child)
		{
			// Queue of gameobjects that still need to be deserialized
			Queue<Owned<GameObject>> unloadedObjects;

			// Do a first pass, instantiate everything
			child.EnumerateChildren([&](auto& gameobject)
			{
				// Find the type of GameObject that this node is referring to
				auto type = Application::FindType(gameobject.GetName());
				
				if (!type || !type->IsCastableTo(TypeOf<GameObject>()))
				{
					// Type isn't a GameObject type, go to next object
					gameobject.MapRefID(nullptr);
					unloadedObjects.Push(nullptr);
				}
				else
				{
					// Instantiate it
					auto object = StaticPointerCast<GameObject>(DynamicNew(*type));

					// Map the address of the new instantiation to the address in the archive
					gameobject.MapRefID(object.GetManagedPointer());
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

					if (object->GetType().IsCastableTo(TypeOf<Entity>()))
					{
						unspawnedEntities.Push(std::move(object));
					}
					else
					{
						unspawnedComponents.Push(std::move(object));
					}
				}
			});
		});

		// Spawn all Entities
		for (auto& entity : unspawnedEntities)
		{
			this->SpawnGameObject(std::move(entity));
		}

		// Spawn all Components
		for (auto& component : unspawnedComponents)
		{
			this->SpawnGameObject(std::move(component));
		}
	}

	void World::Update()
	{
		Events.DispatchEvent("Update", this->TimeDilation);
		Events.Flush();

		// Remove stale objects
		while (!_destroyedObjects.IsEmpty())
		{
			auto object = _destroyedObjects.Pop();
			_entities.Remove(object->GetID());
			_components.Remove(object->GetID());
			_gameObjects.Remove(object->GetID());
		}

		for (auto& system : _systems)
		{
			system->Update(*this);
		}

		for (auto& system : _systems)
		{
			// TODO: Make this asynchronous
			system->PostUpdate(*this);
		}
	}

	void World::DestroyGameObject(GameObject& object)
	{
		assert(object._state >= GameObject::State::Spawned);

		if (object._state != GameObject::State::Destroyed)
		{
			object._state = GameObject::State::Destroyed;
			_destroyedObjects.Push(&object);
			object.OnDestroy();
		}
	}

	void World::SpawnGameObject(Owned<GameObject> owner)
	{
		auto& object = *owner;
		
		// Give the object an ID
		assert(object._state == GameObject::State::Uninitialized);
		object._id = _nextGameObjectID++;
		object._state = GameObject::State::Initialized;
		
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
		object._state = GameObject::State::Spawning;
		object.OnSpawn();
		object._state = GameObject::State::Spawned;
	}
}
