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
		// Reset state
		_gameObjects.Clear();
		_destroyedObjects.Clear();
		_entities.Clear();
		_components.Clear();
		_nextGameObjectID = 1;

		// Begin deserialization
		reader.PullValue("TimeDilation", this->TimeDilation);
		reader.PullValue("TimeStep", this->TimeStep);
		reader.PullValue("NextID", _nextGameObjectID);
		
		// Queue of GameObjects that still need to be spawned
		Queue<Owned<GameObject>> uninitialized_entities;
		Queue<Owned<GameObject>> unititialized_component;
		
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
						uninitialized_entities.Push(std::move(object));
					}
					else
					{
						unititialized_component.Push(std::move(object));
					}
				}
			});
		});

		// Spawn all Entities
		for (auto& owner : uninitialized_entities)
		{
			auto& entity = *owner;
			this->InitializeGameobject(std::move(owner), entity._id);
			
			// Serialized entities do not get their 'OnSpawn' handler called
			entity._state = GameObject::State::Spawned;
		}

		// Spawn all Components
		for (auto& owner : unititialized_component)
		{
			auto& component = *owner;
			this->InitializeGameobject(std::move(owner), component._id);
			
			// Serialized entities do not get their 'OnSpawn' handler called
			component._state = GameObject::State::Spawned;
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

	void World::SetGravity(const Vec3& gravity)
	{
		_gravity = gravity;
		// TODO: Update this with PhysicsSystem
	}

	void World::InitializeGameobject(Owned<GameObject> owner, GameObject::ID id)
	{	
		auto& object = *owner;
		assert(object._state == GameObject::State::Uninitialized);

		// Add it to the world
		_gameObjects[id] = std::move(owner);
		if (auto entity = Cast<Entity>(object))
		{
			_entities[id] = entity;
		}
		else if (auto component = Cast<Component>(object))
		{
			_components[id] = component;
		}

		// Initialize the object
		object._id = id;
		object._world = this;
		object._state = GameObject::State::Initialized;
		object.OnInitialize();
	}

	void World::SpawnGameObject(GameObject& object)
	{
		// Spawn the object
		assert(object._state == GameObject::State::Initialized);
		object._state = GameObject::State::Spawning;
		object.OnSpawn();
		object._state = GameObject::State::Spawned;
	}
}
