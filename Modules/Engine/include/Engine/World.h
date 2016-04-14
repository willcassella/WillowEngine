// World.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Containers/Queue.h>
#include <Core/Event/EventManager.h>
#include "Component.h"
#include "System.h"
#include "Handle.h"

/////////////////
///   Types   ///

namespace Willow
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

		EventManager Events;
		float TimeDilation = 1.f;
		float TimeStep = 1.f / 60;

		///////////////////
		///   Methods   ///
	public:

		void ToArchive(ArchiveWriter& writer) const;

		/** Sets the state of this world from the given archive. 
		* NOTE: This resets the state of the World. */
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
			this->InitializeGameobject(std::move(owner), _nextGameObjectID++);

			// Spawn it
			this->SpawnGameObject(entity);
			return entity;
		}
		
		/** Spawns a new instance of the given type of Component into the World. */
		template <class T>
		auto Spawn() -> std::enable_if_t<std::is_base_of<Component, T>::value, T&>
		{
			auto& entity = this->Spawn<Entity>();
			return this->Spawn<T>(entity);
		}

		template <class T>
		auto Spawn(Entity& entity) -> std::enable_if_t<std::is_base_of<Component, T>::value, T&>
		{
			// Create a new Component
			auto owner = New<T>();
			auto& component = *owner;

			// Initialize it
			component._entity = &entity;
			entity._components.Add(&component);
			this->InitializeGameobject(std::move(owner), _nextGameObjectID++);

			// Spawn it
			this->SpawnGameObject(component);
			return component;
		}

		/** Spawns a new instance of the given type with the given name into the World. */
		template <class T>
		auto Spawn(String name) -> std::enable_if_t<std::is_base_of<Entity, T>::value, T&>
		{
			// Create a new entity
			auto owner = New<T>();
			auto& entity = *owner;

			// Initialize it
			entity._name = std::move(name);
			this->InitializeGameobject(std::move(owner), _nextGameObjectID++);

			// Spawn it
			this->SpawnGameObject(entity);
			return entity;
		}

		/** Spawns a new instance of the given type with the given name into the World. */
		template <class T>
		auto Spawn(String name) -> std::enable_if_t<std::is_base_of<Component, T>::value, T&>
		{
			auto& entity = this->Spawn<Entity>(std::move(name));
			return this->Spawn<T>(entity);
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

		template <class T>
		void Require() const
		{
			assert(this->GetSystem<T>() != nullptr);
		}

		/** Adds the given system to this World. */
		void AddSystem(System& system)
		{
			_systems.Add(&system);
		}

		/** Retreives the specified type of System from this world.
		* NOTE: Returns 'null' if the given type of System has not been added to this World. */
		template <class T>
		T* GetSystem() const
		{
			for (auto system : _systems)
			{
				if (auto pSystem = Cast<T>(*system))
				{
					return pSystem;
				}
			}

			return nullptr;
		}

		/** Returns the current gravity in this World. */
		Vec3 GetGravity() const
		{
			return _gravity;
		}

		/** Sets the gravity in this World. */
		void SetGravity(const Vec3& gravity);

		/** Returns a pointer to the object referred to by the given handle. 
		* NOTE: Returns 'null' if the object in question no longer exists. */
		template <class T>
		T* Get(Handle<T> handle)
		{
			return const_cast<T*>(stde::as_const(*this).Get(handle));
		}

		/** Returns a pointer to the object referred to by the given handle. 
		* NOTE: Returns 'null' if the object in question no longer exists. */
		template <class T>
		const T* Get(Handle<T> handle) const
		{
			const T* result = nullptr;
			_gameObjects.Find(handle.GetID(), [&result](const auto& object)
			{
				result = static_cast<const T*>(object.GetManagedPointer());
			});

			return result;
		}

	private:

		/** Initializes the given GameObject in this World. 
		* Note: The caller is responsible for initialize all state of this GameObject other than the ID. */
		void InitializeGameobject(Owned<GameObject> object, GameObject::ID id);

		/** Spawns the given GameObject into this World.
		* NOTE: The caller is responsible for having previously initialized the given GameObject in this World. */
		void SpawnGameObject(GameObject& object);

		////////////////
		///   Data   ///
	private:

		/** World Data */
		GameObject::ID _nextGameObjectID;
		Table<GameObject::ID, Owned<GameObject>> _gameObjects;
		Queue<GameObject*> _destroyedObjects;

		Table<GameObject::ID, Entity*> _entities;
		Table<Component::ID, Component*> _components;
		Array<System*> _systems; // TODO: Make this weak

		/** Physics data */
		Vec3 _gravity;
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
		return this->GetWorld().Spawn<T>(*this);
	}
}
