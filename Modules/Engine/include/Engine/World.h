// World.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Containers/Queue.h>
#include <Core/Event/EventManager.h>
#include "Component.h"
#include "System.h"

/////////////////
///   Types   ///

namespace Willow
{
	/* World class contains all game objects and world information */
	class ENGINE_API World final : public Object
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

		/** World update settings. */
		EventManager Events;
		float TimeDilation = 1.f;
		float TimeStep = 1.f / 60;

		///////////////////
		///   Methods   ///
	public:

		void ToArchive(ArchiveWriter& writer) const;

		void FromArchive(const ArchiveReader& reader);

		/** Updates the state of this World by one time step. */
		void Update();

		/** Spawns a new instance of the given type into the World. */
		template <class T>
		auto Spawn() -> std::enable_if_t<std::is_base_of<Entity, T>::value, T&>
		{
			// Create a new entity
			auto owner = New<T>();
			auto& entity = *owner;
			
			// Initialize it
			entity._world = this;

			// Spawn it
			this->SpawnGameObject(std::move(owner));
			return entity;
		}

		/** Spawns a new instance of the given type into the World. */
		template <class T>
		auto Spawn() -> std::enable_if_t<std::is_base_of<Component, T>::value, T&>
		{
			return this->Spawn<Entity>().Connect<T>();
		}

		/** Spawns a new instance of the given type with the given name into the World. */
		template <class T>
		auto Spawn(String name) -> std::enable_if_t<std::is_base_of<Entity, T>::value, T&>
		{
			// Create a new entity
			auto owner = New<T>();
			auto& entity = *owner;

			// Initialize it
			entity._world = this;
			entity._name = std::move(name);

			// Spawn it
			this->SpawnGameObject(std::move(owner));
			return entity;
		}

		/** Spawns a new instance of the given type with the given name into the World. */
		template <class T>
		auto Spawn(String name) -> std::enable_if_t<std::is_base_of<Component, T>::value, T&>
		{
			return this->Spawn<Entity>(std::move(name)).Connect<T>();
		}

		/** Returns an enumeration of the given types of objects in this World. */
		template <typename T>
		auto Enumerate() const
		{
			static_assert(std::is_base_of<GameObject, T>::value, "The given type does not exist in this World.");

			Array<const T*> result;

			if (std::is_base_of<Entity, T>::value)
			{
				for (auto entity : _entities)
				{
					if (auto e = Cast<const T>(*entity.Second))
					{
						result.Add(e);
					}
				}
			}
			else if (std::is_base_of<Component, T>::value)
			{
				for (auto component : _components)
				{
					if (auto c = Cast<const T>(*component.Second))
					{
						result.Add(c);
					}
				}
			}
			else
			{
				for (const auto& gameObject : _gameObjects)
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
		void DestroyGameObject(GameObject& object);

		/** Spawns the given GameObject into this World.
		* NOTE: The caller is responsible for initializing all state of this GameObject other than the ID. */
		void SpawnGameObject(Owned<GameObject> owner);

		/** Adds the given system to this World. */
		template <typename T>
		T& AddSystem()
		{
			auto owner = New<T>(*this);
			auto& system = *owner;

			_systems.Add(std::move(owner));
			return system;
		}

		/** Returns the current gravity in this World. */
		Vec3 GetGravity() const
		{
			return _gravity;
		}

		/** Sets the gravity in this World. */
		void SetGravity(const Vec3& gravity);

		/** Returns the physics world for this World. 
		* NOTE: This method is for internal use only. */
		PhysicsWorld& INTERNAL_GetPhysicsWorld();

		/** Returns the physics world for this World. 
		* NOTE: This method is for internal use only. */
		const PhysicsWorld& INTERNAL_GetPhysicsWorld() const;

		////////////////
		///   Data   ///
	private:

		GameObject::ID _nextGameObjectID;
		Table<GameObject::ID, Owned<GameObject>> _gameObjects;
		Queue<GameObject*> _destroyedObjects;

		Table<GameObject::ID, Entity*> _entities;
		Table<Component::ID, Component*> _components;
		Array<Owned<System>> _systems;

		/** Physics state. */
		Vec3 _gravity;
		std::unique_ptr<PhysicsWorld> _physicsWorld;
	};

	///////////////////
	///   Methods   ///

	template <class T>
	T& Entity::Attach()
	{
		auto& object = this->GetWorld().Spawn<T>();
		object.SetParent(this, SP_MoveToOrigin);
		return object;
	}

	template <class T>
	T& Entity::Attach(String name)
	{
		auto& object = this->GetWorld().Spawn<T>(std::move(name));
		object.SetParent(this, SP_MoveToOrigin);
		return object;
	}

	template <class T>
	T& Entity::Connect()
	{
		static_assert(std::is_base_of<Component, T>::value, "You can only connect Component types to Entities.");

		// Construct the Component
		auto owner = New<T>();
		auto& component = *owner;

		// Register the Component with this Entity
		component._entity = this;
		this->_components.Add(&component);

		// Spawn it into the world
		this->GetWorld().SpawnGameObject(std::move(owner));
		return component;
	}
}
