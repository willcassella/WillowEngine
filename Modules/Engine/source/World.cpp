// World.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Engine/World.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::World)
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
		this->reset();
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
			for (const auto& kv : this->_object_table)
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
		Queue<GameObject*> uninitializedEntities;
		Queue<GameObject*> unititializedComponents;
		
		// Load all entities/components
		reader.GetChild("objects", [&](auto& child)
		{
			// Queue of gameobjects that still need to be deserialized
			Queue<GameObject*> unloadedObjects;

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
					auto& object = this->create_object(*static_cast<const ClassInfo*>(type));

					// Map the address of the new instantiation to the address in the archive
					gameobject.MapRefID(&object);
					unloadedObjects.Push(&object);
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
						uninitializedEntities.Push(object);
					}
					else
					{
						unititializedComponents.Push(object);
					}
				}
			});
		});

		// Spawn all Entities
		for (auto entity : uninitializedEntities)
		{
			this->initialize_object(*entity, entity->_id);
			
			// Serialized entities do not get their 'on_spawn' handler called
			entity->_state = GameObject::State::Spawned;
		}

		// Spawn all Components
		for (auto component : unititializedComponents)
		{
			this->initialize_object(*component, component->_id);
			
			// Serialized entities do not get their 'on_spawn' handler called
			component->_state = GameObject::State::Spawned;
		}
	}

	void World::update()
	{
		// Copy event bindings and instances onto stack (prevents issues with binding/dispatching events during event dispatch)
		auto eventBindings = this->_event_bindings;
		auto events = std::move(this->_current_frame.events); // NOTE: It's safe to move 'EventQueue' multiple times

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

		// Update systems
		for (auto& system : this->_systems)
		{
			system->update(*this);
		}

		// Remove destroyed objects
		while (!this->_current_frame.destroyed_objects.IsEmpty())
		{
			auto object = _current_frame.destroyed_objects.Pop();
			
			// Get its type
			auto* type = &object->GetType();

			// Remove it from the table and call destructor
			_object_table.Remove(object->get_id());
			object->~GameObject();

			// Mark the slot as empty
			_object_storage.Find(type)->set_slot_empty(reinterpret_cast<byte*>(object));
		}
	}

	Entity& World::spawn(SubClassOf<Entity> type)
	{
		assert(!type.is_null());

		// Instantiate the object
		auto& entity = static_cast<Entity&>(this->create_object(type));

		// Initialize it
		this->initialize_object(entity, this->_next_object_id++);
		
		// Spawn it
		this->spawn_object(entity);
		return entity;
	}

	Entity& World::spawn(SubClassOf<Entity> type, String name)
	{
		assert(!type.is_null());

		// Instantiate the object
		auto& entity = static_cast<Entity&>(this->create_object(type));

		// Initialize it
		entity._name = std::move(name);
		this->initialize_object(entity, this->_next_object_id++);

		// Spawn it
		this->spawn_object(entity);
		return entity;
	}

	void World::destroy_object(GameObject& object)
	{
		assert(object._state >= GameObject::State::Spawned);

		if (object._state != GameObject::State::Destroyed)
		{
			object._state = GameObject::State::Destroyed;
			this->_current_frame.destroyed_objects.Push(&object);
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
		// Destroy all the objects
		for (auto object : _object_table)
		{
			object.Second->~GameObject();
		}

		_object_table.Clear();
		_object_storage.Clear();
		_event_bindings.Clear();
		_current_frame.destroyed_objects.Clear();
		_current_frame.events.clear();

		this->_next_object_id = 1;
	}

	void World::initialize_object(GameObject& object, GameObject::ID id)
	{	
		assert(object._state == GameObject::State::Uninitialized);

		// Add it to the world
		this->_object_table[id] = &object;

		// Initialize the object
		object._id = id;
		object._world = this;
		object._state = GameObject::State::Initialized;
		object.on_initialize();
	}

	GameObject& World::create_object(SubClassOf<GameObject> type)
	{
		assert(!type.is_null());

		// Get the buffer for this type
		LinkedBuffer* buffer = _object_storage.Find(type.get_class());
		
		// If we don't have a buffer, create one
		if (!buffer)
		{
			buffer = &_object_storage.Insert(type.get_class(), LinkedBuffer{ type.get_class()->get_size() });
		}

		// Get a slot for the object and construct it
		byte* slot = buffer->get_empty_slot();
		type.get_class()->get_default_constructor()(slot);

		return reinterpret_cast<GameObject&>(*slot);
	}

	void World::spawn_object(GameObject& object)
	{
		assert(object._state == GameObject::State::Initialized);
		
		// Spawn the object
		object._state = GameObject::State::Spawning;
		object.on_spawn();
		object._state = GameObject::State::Spawned;
	}
}
