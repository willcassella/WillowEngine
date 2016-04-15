// World.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Containers/Queue.h>
#include <Core/Event/EventManager.h>
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

		////////////////////////
		///   Constructors   ///
	public:

		World();
		~World() override;

		//////////////////
		///   Fields   ///
	public:

		EventManager events;
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

		/** Spawns a new instance of the given type into the World. */
		template <class T>
		auto spawn() -> std::enable_if_t<std::is_base_of<Entity, T>::value, T&>
		{
			// Create a new entity
			auto owner = New<T>();
			auto& entity = *owner;
			
			// Initialize it
			this->intialize_object(std::move(owner), this->_next_object_id++);

			// Spawn it
			this->spawn_object(entity);
			return entity;
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
			auto owner = New<T>();
			auto& component = *owner;

			// Initialize it
			component._entity = &entity;
			entity._components.Add(&component);
			this->intialize_object(std::move(owner), this->_next_object_id++);

			// Spawn it
			this->spawn_object(component);
			return component;
		}

		/** Spawns a new instance of the given type with the given name into the World. */
		template <class T>
		auto spawn(String name) -> std::enable_if_t<std::is_base_of<Entity, T>::value, T&>
		{
			// Create a new entity
			auto owner = New<T>();
			auto& entity = *owner;

			// Initialize it
			entity._name = std::move(name);
			this->intialize_object(std::move(owner), this->_next_object_id++);

			// Spawn it
			this->spawn_object(entity);
			return entity;
		}

		/** Spawns a new instance of the given type with the given name into the World. */
		template <class T>
		auto spawn(String name) -> std::enable_if_t<std::is_base_of<Component, T>::value, T&>
		{
			auto& entity = this->spawn<Entity>(std::move(name));
			return this->spawn<T>(entity);
		}

		/** Returns an enumeration of the given types of objects in this World. */
		template <typename T>
		auto enumerate() const
		{
			static_assert(std::is_base_of<GameObject, T>::value, "The given type does not exist in this World.");

			Array<const T*> result;

			if (std::is_base_of<Entity, T>::value)
			{
				for (auto entity : this->_entities)
				{
					if (auto e = Cast<const T>(*entity.Second))
					{
						result.Add(e);
					}
				}
			}
			else if (std::is_base_of<Component, T>::value)
			{
				for (auto component : this->_components)
				{
					if (auto c = Cast<const T>(*component.Second))
					{
						result.Add(c);
					}
				}
			}
			else
			{
				for (const auto& gameObject : this->_objects)
				{
					if (auto g = Cast<const T>(*gameObject.Second))
					{
						result.Add(g);
					}
				}
			}

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
		T* get(Handle<T> handle)
		{
			return const_cast<T*>(stde::as_const(*this).get(handle));
		}

		/** Returns a pointer to the object referred to by the given handle. 
		* NOTE: Returns 'null' if the object in question no longer exists. */
		template <class T>
		const T* get(Handle<T> handle) const
		{
			const T* result = nullptr;
			this->_objects.Find(handle.get_id(), [&result](const auto& object)
			{
				result = static_cast<const T*>(object.GetManagedPointer());
			});

			return result;
		}

		/** Resets the state of this World. */
		void reset();

	private:

		/** Initializes the given GameObject in this World. 
		* Note: The caller is responsible for initialize all state of this GameObject other than the ID. */
		void intialize_object(Owned<GameObject> object, GameObject::ID id);

		/** Spawns the given GameObject into this World.
		* NOTE: The caller is responsible for having previously initialized the given GameObject in this World. */
		void spawn_object(GameObject& object);

		////////////////
		///   Data   ///
	private:

		/** World Data */
		GameObject::ID _next_object_id;
		Table<GameObject::ID, Owned<GameObject>> _objects;
		Queue<GameObject*> _destroyed_objects;

		Table<GameObject::ID, Entity*> _entities;
		Table<Component::ID, Component*> _components;
		Array<System*> _systems; // TODO: Make this weak

		/** Physics data */
		Vec3 _gravity;
	};

	///////////////////
	///   Methods   ///

	template <class T>
	T& Entity::attach()
	{
		auto& object = this->get_world().spawn<T>();
		object.set_parent(this, SP_Move_To_Origin);
		return object;
	}

	template <class T>
	T& Entity::attach(String name)
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
}
