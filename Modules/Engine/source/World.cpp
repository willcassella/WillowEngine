// World.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Engine/World.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::World)
.Data("objects", &World::_objects, DF_Transient)
.Data("entities", &World::_entities, DF_Transient)
.Data("components", &World::_components, DF_Transient)
.Data("destroyed_objects", &World::_destroyed_objects, DF_Transient)
.Data("next_object_id", &World::_next_object_id)
.Field("time_dilation", &World::time_dilation, "The time dilation of the world. Default is 1.")
.Field("time_step", &World::time_step, "The amount of time (ms) that each update of the world represents.");

namespace willow
{
	////////////////////////
	///   Constructors   ///

	World::World()
		: _next_object_id{ 1 }
	{
		// All done
	}

	World::~World()
	{
		// All done
	}

	///////////////////
	///   Methods   ///
	
	void World::ToArchive(ArchiveWriter& writer) const
	{
		writer.PushValue("time_dilation", this->time_dilation);
		writer.PushValue("time_step", this->time_step);
		writer.PushValue("next_object_id", this->_next_object_id);
		
		// Save all entites/components
		writer.AddChild("objects", [this](auto& child)
		{
			for (const auto& kv : this->_objects)
			{
				// Push the given value into this archive, wrapping it in a Node containing its type name and address
				child.PushReferencedValue(kv.Second->GetType().get_name(), *kv.Second);
			}
		});
	}

	void World::FromArchive(const ArchiveReader& reader)
	{
		// Reset state
		this->reset();

		// Begin deserialization
		reader.PullValue("time_dilation", this->time_dilation);
		reader.PullValue("time_step", this->time_step);
		reader.PullValue("next_object_id", this->_next_object_id);
		
		// Queue of GameObjects that still need to be spawned
		Queue<Owned<GameObject>> uninitializedEntities;
		Queue<Owned<GameObject>> unititializedComponents;
		
		// Load all entities/components
		reader.GetChild("objects", [&](auto& child)
		{
			// Queue of gameobjects that still need to be deserialized
			Queue<Owned<GameObject>> unloadedObjects;

			// Do a first pass, instantiate everything
			child.EnumerateChildren([&](auto& gameobject)
			{
				// Find the type of GameObject that this node is referring to
				auto type = Application::FindType(gameobject.GetName());
				
				if (!type || !type->is_castable_to(TypeOf<GameObject>()))
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

					if (object->GetType().is_castable_to(TypeOf<Entity>()))
					{
						uninitializedEntities.Push(std::move(object));
					}
					else
					{
						unititializedComponents.Push(std::move(object));
					}
				}
			});
		});

		// Spawn all Entities
		for (auto& owner : uninitializedEntities)
		{
			auto& entity = *owner;
			this->intialize_object(std::move(owner), entity._id);
			
			// Serialized entities do not get their 'on_spawn' handler called
			entity._state = GameObject::State::Spawned;
		}

		// Spawn all Components
		for (auto& owner : unititializedComponents)
		{
			auto& component = *owner;
			this->intialize_object(std::move(owner), component._id);
			
			// Serialized entities do not get their 'on_spawn' handler called
			component._state = GameObject::State::Spawned;
		}
	}

	void World::update()
	{
		// Copy event bindings and instances onto stack (prevents issues with binding/dispatching events during event dispatch)
		auto eventBindings = this->_event_bindings;
		auto events = std::move(this->_events); // NOTE: It's safe to move 'EventQueue' multiple times

		// Push 'Update' event
		events.push_event("update", this->time_step * this->time_dilation);

		// Flush events
		events.enumerate([&](const String& event, const TypeInfo* argType, const void* argValue)
		{
			auto* bindings = eventBindings.Find(event);

			// If there's anything bound to this event
			if (bindings)
			{
				// For each binding for the event
				for (const auto& binding : *bindings)
				{
					// If the handler argument is compatible with the event argument
					if (!binding.second.accepts_argument() || argType && argType->is_castable_to(binding.second.get_arg_type()))
					{
						// Get the object to handle the event
						auto* object = this->get_object(binding.first);
						
						// If the object still exists
						if (object)
						{
							binding.second.invoke(object, argValue);
						}
					}
				}
			}
		});

		// Remove destroyed objects
		while (!this->_destroyed_objects.IsEmpty())
		{
			auto object = _destroyed_objects.Pop();
			this->_entities.Remove(object->get_id());
			this->_components.Remove(object->get_id());
			this->_objects.Remove(object->get_id());
		}

		for (auto& system : this->_systems)
		{
			system->update(*this);
		}

		for (auto& system : this->_systems)
		{
			// TODO: Make this asynchronous
			system->post_update(*this);
		}
	}

	Entity& World::spawn(SubClassOf<Entity> type)
	{
		assert(!type.is_null());

		// Instantiate the object
		auto owner = StaticPointerCast<Entity>(DynamicNew(*type.get_class()));
		auto& entity = *owner;

		// Spawn it
		this->intialize_object(std::move(owner), this->_next_object_id++);
		this->spawn_object(entity);

		return entity;
	}

	Entity& World::spawn(SubClassOf<Entity> type, String name)
	{
		assert(!type.is_null());

		// Instantiate the object
		auto owner = StaticPointerCast<Entity>(DynamicNew(*type.get_class()));
		auto& entity = *owner;
		
		// Spawn it
		entity._name = std::move(name);
		this->intialize_object(std::move(owner), this->_next_object_id++);
		this->spawn_object(entity);

		return entity;
	}

	void World::destroy_object(GameObject& object)
	{
		assert(object._state >= GameObject::State::Spawned);

		if (object._state != GameObject::State::Destroyed)
		{
			object._state = GameObject::State::Destroyed;
			this->_destroyed_objects.Push(&object);
			object.on_destroy();
		}
	}

	void World::set_gravity(const Vec3& gravity)
	{
		this->_gravity = gravity;
		// TODO: Update this with PhysicsSystem
	}

	void World::reset()
	{
		this->_objects.Clear();
		this->_destroyed_objects.Clear();
		this->_entities.Clear();
		this->_components.Clear();
		this->_next_object_id = 1;
	}

	void World::intialize_object(Owned<GameObject> owner, GameObject::ID id)
	{	
		auto& object = *owner;
		assert(object._state == GameObject::State::Uninitialized);

		// Add it to the world
		this->_objects[id] = std::move(owner);
		if (auto entity = Cast<Entity>(object))
		{
			this->_entities[id] = entity;
		}
		else if (auto component = Cast<Component>(object))
		{
			this->_components[id] = component;
		}

		// Initialize the object
		object._id = id;
		object._world = this;
		object._state = GameObject::State::Initialized;
		object.on_initialize();
	}

	void World::spawn_object(GameObject& object)
	{
		// Spawn the object
		assert(object._state == GameObject::State::Initialized);
		object._state = GameObject::State::Spawning;
		object.on_spawn();
		object._state = GameObject::State::Spawned;
	}
}
