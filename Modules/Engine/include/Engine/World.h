// World.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Memory/Buffers/LinkedBuffer.h>
#include <Core/Containers/Queue.h>
#include <Core/Reflection/SubClassOf.h>
#include <Core/Event/EventHandler.h>
#include <Core/Event/EventQueue.h>
#include "Component.h"
#include "System.h"
#include "Handle.h"

/////////////////
///   Types   ///

namespace willow
{
	/** World class contains all game objects and world information */
	class ENGINE_API World : public Object
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Object)

		/////////////////
		///   Types   ///
	public:

		struct Frame final
		{
			Queue<GameObject*> destroyed_objects;
			EventQueue events;
		};

		////////////////////////
		///   Constructors   ///
	public:

		World();
		World(World&& world) = delete;
		~World() override;

		//////////////////
		///   Fields   ///
	public:

		float time_dilation = 1.f;
		float time_step = 1.f / 60;

		///////////////////
		///   Methods   ///
	public:

		void ToArchive(ArchiveWriter& writer) const;

		/** Sets the state of this world from the given archive. 
		* NOTE: This resets the state of the World. */
		void FromArchive(const ArchiveReader& reader);

		/** Updates the state of this World by one time step. */
		void update();

		/** Spawns a new instance of the given type. 
		* WARNING: 'type' must not be null. */
		Entity& spawn(SubClassOf<Entity> type);

		/** Spawns a new instance of the given type, with the given name.
		* WARNING: 'type' must not be null. */
		Entity& spawn(SubClassOf<Entity> type, String name);

		/** Spawns a new instance of the given type into the World. */
		template <class T>
		auto spawn() -> std::enable_if_t<std::is_base_of<Entity, T>::value, T&>
		{
			return static_cast<T&>(this->spawn(TypeOf<T>()));
		}
		
		/** Spawns a new instance of the given type of Component into the World. */
		template <class T>
		auto spawn() -> std::enable_if_t<std::is_base_of<Component, T>::value, T&>
		{
			auto& entity = this->spawn<Entity>();
			return this->spawn<T>(entity);
		}

		template <class T>
		auto spawn(Entity& entity) -> std::enable_if_t<std::is_base_of<Component, T>::value, T&>
		{
			// Create a new Component
			auto& component = static_cast<T&>(this->create_object(TypeOf<T>()));

			// Initialize it
			component._entity = &entity;
			entity._components.Add(&component);
			this->initialize_object(component, this->_next_object_id++);

			// Spawn it
			this->spawn_object(component);
			return component;
		}

		/** Spawns a new instance of the given type with the given name into the World. */
		template <class T>
		auto spawn(String name) -> std::enable_if_t<std::is_base_of<Entity, T>::value, T&>
		{
			return static_cast<T&>(this->spawn(TypeOf<T>(), std::move(name)));
		}

		/** Spawns a new instance of the given type with the given name into the World. */
		template <class T>
		auto spawn(String name) -> std::enable_if_t<std::is_base_of<Component, T>::value, T&>
		{
			auto& entity = this->spawn<Entity>(std::move(name));
			return this->spawn<T>(entity);
		}

		/** Enumeras all objects of the given type in this World. */
		template <typename T, typename F>
		void enumerate_objects(F func) const
		{
			static_assert(std::is_base_of<GameObject, T>::value, "The given type does not exist in this World.");

			// For each type in this world
			for (const auto& type : _object_storage)
			{
				// If the type is castable to 'T'
				if (type.First->is_castable_to(TypeOf<T>()))
				{
					// Add all instances of that type
					type.Second.enumerate_unempty([&func](const byte* ptr)
					{
						func(*reinterpret_cast<const T*>(ptr));
					});
				}
			}
		}

		/** Enumeras all objects of the given type in this World. */
		template <typename T>
		auto enumerate_objects() const
		{
			Array<const T*> result;

			this->enumerate_objects<T>([&result](const T& object)
			{
				result.Add(&object);
			});

			return result;
		}

		/** Enumeras all objects of the given type in this World. */
		template <typename T>
		auto enumerate_objects()
		{
			Array<T*> result;

			this->enumerate_objects<T>([&result](const T& object)
			{
				result.Add(const_cast<T*>(&object));
			});

			return result;
		}

		/** Destroys the given GameObject at the end of the frame. */
		void destroy_object(GameObject& object);

		template <class T>
		void require_system() const
		{
			assert(this->get_system<T>() != nullptr);
		}

		/** Adds the given system to this World. */
		void add_system(System& system)
		{
			this->_systems.Add(&system);
		}

		/** Retreives the specified type of System from this world.
		* NOTE: Returns 'null' if the given type of System has not been added to this World. */
		template <class T>
		T* get_system() const
		{
			for (auto system : this->_systems)
			{
				if (auto pSystem = Cast<T>(*system))
				{
					return pSystem;
				}
			}

			return nullptr;
		}

		/** Returns the current gravity in this World. */
		Vec3 get_gravity() const
		{
			return this->_gravity;
		}

		/** Sets the gravity in this World. */
		void set_gravity(const Vec3& gravity);

		/** Returns a pointer to the object referred to by the given handle. 
		* NOTE: Returns 'null' if the object in question no longer exists. */
		template <class T>
		T* get_object(Handle<T> handle)
		{
			return const_cast<T*>(stde::as_const(*this).get_object(handle));
		}

		/** Returns a pointer to the object referred to by the given handle. 
		* NOTE: Returns 'null' if the object in question no longer exists. */
		template <class T>
		const T* get_object(Handle<T> handle) const
		{
			const T* result = nullptr;
			this->_object_table.Find(handle.get_id(), [&result](auto object)
			{
				result = static_cast<const T*>(object);
			});

			return result;
		}

		/** Resets the state of this World. */
		void reset();

		template <class T, typename HandlerT>
		void bind_event(const String& name, T& object, HandlerT handler)
		{
			this->_event_bindings[name].Add(std::make_pair(Handle<GameObject>{ object }, EventHandler{ handler }));
		}

		/** Pushes the given event onto the event queue. */
		void push_event(String name)
		{
			this->_current_frame.events.push_event(std::move(name));
		}

		/** Pushes the given event with the given argument onto the event queue. */
		template <typename T>
		void push_event(String name, T value)
		{
			this->_current_frame.events.push_event(std::move(name), std::move(value));
		}

	private:

		/** Allocates and constructs a new instance of the given type of object
		* NOTE: This does not initialize or spawn the object. */
		GameObject& create_object(SubClassOf<GameObject> type);

		/** Initializes the given GameObject in this World. 
		* Note: The caller is responsible for initialize all state of this GameObject other than the ID. */
		void initialize_object(GameObject& object, GameObject::ID id);

		/** Spawns the given GameObject into this World.
		* NOTE: The caller is responsible for having previously initialized the given GameObject in this World
		* NOTE: This should not be called for objects loaded from an Archive, as they have already been "spawned". */
		void spawn_object(GameObject& object);

		////////////////
		///   Data   ///
	private:

		/** World Data */
		GameObject::ID _next_object_id;
		Table<GameObject::ID, GameObject*> _object_table;
		Table<const ClassInfo*, LinkedBuffer> _object_storage;
		Array<System*> _systems; // TODO: Figure out a better way of doing this

		/** Physics data */
		Vec3 _gravity;

		/* Event data */
		Table<String, Array<std::pair<Handle<GameObject>, EventHandler>>> _event_bindings;

		/* Frame data */
		Frame _current_frame;
	};

	///////////////////
	///   Methods   ///

	template <class T>
	auto Entity::attach() -> std::enable_if_t<std::is_base_of<Component, T>::value, T&>
	{
		auto& object = this->get_world().spawn<T>();
		object.get_entity().set_parent(this, SP_Move_To_Origin);
		return object;
	}

	template <class T>
	auto Entity::attach() -> std::enable_if_t<std::is_base_of<Entity, T>::value, T&>
	{
		auto& object = this->get_world().spawn<T>();
		object.set_parent(this, SP_Move_To_Origin);
		return object;
	}

	template <class T>
	auto Entity::attach(String name) -> std::enable_if_t<std::is_base_of<Component, T>::value, T&>
	{
		auto& object = this->get_world().spawn<T>(std::move(name));
		object.get_entity().set_parent(this, SP_Move_To_Origin);
		return object;
	}

	template <class T>
	auto Entity::attach(String name) -> std::enable_if_t<std::is_base_of<Entity, T>::value, T&>
	{
		auto& object = this->get_world().spawn<T>(std::move(name));
		object.set_parent(this, SP_Move_To_Origin);
		return object;
	}

	template <class T>
	T& Entity::connect()
	{
		return this->get_world().spawn<T>(*this);
	}

	template <class T>
	T* Handle<T>::get_object(World& world) const
	{
		return world.get_object(*this);
	}

	template <class T>
	const T* Handle<T>::get_object(const World& world) const
	{
		return world.get_object(*this);
	}
}
