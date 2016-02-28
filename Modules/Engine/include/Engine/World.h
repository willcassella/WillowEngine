// World.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <memory>
#include <Core/Misc/SerializeableObject.h>
#include <Core/Containers/Queue.h>
#include <Core/Event/EventManager.h>
#include "Forwards/Physics.h"
#include "Component.h"

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
		std::enable_if_t<std::is_base_of<Entity, T>::value, T&> Spawn()
		{
			auto& entity = this->InitializeGameObject(New<T>());
			entity._world = this;
			entity.Spawn();

			return entity;
		}

		/** Spawns a new instance of the given type into the World. */
		template <class T>
		std::enable_if_t<std::is_base_of<Component, T>::value, T&> Spawn()
		{
			return this->Spawn<Entity>().Connect<T>();
		}

		/** Spawns a new instance of the given type with the given name into the World. */
		template <class T>
		std::enable_if_t<std::is_base_of<Entity, T>::value, T&> Spawn(String name)
		{
			auto& entity = this->Spawn<T>();
			entity._name = std::move(name);

			return entity;
		}

		/** Spawns a new instance of the given type with the given name into the World. */
		template <class T>
		std::enable_if_t<std::is_base_of<Component, T>::value, T&> Spawn(String name)
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

		/** Returns the physics world for this World. */
		FORCEINLINE PhysicsWorld& GetPhysicsWorld()
		{
			return *_physicsWorld;
		}

		/** Returns the physics world for this World. */
		FORCEINLINE const PhysicsWorld& GetPhysicsWorld() const
		{
			return *_physicsWorld;
		}

		/** Initializes the given GameObject in this World.
		* NOTE: This does not call "GameObject::Spawn()".
		* That is the caller's responsibility. */
		template <class T>
		T& InitializeGameObject(Owned<T> object)
		{
			auto& ref = *object;
			ref.Initialize(_nextGameObjectID++);
			_gameObjects[ref.GetID()] = std::move(object);

			if (std::is_base_of<Entity, T>::value)
			{
				_entities[ref.GetID()] = reinterpret_cast<Entity*>(&ref);
			}
			else if (std::is_base_of<Component, T>::value)
			{
				_components[ref.GetID()] = reinterpret_cast<Component*>(&ref);
			}

			return ref;
		}

		////////////////
		///   Data   ///
	private:

		GameObject::ID _nextGameObjectID;
		Table<GameObject::ID, Owned<GameObject>> _gameObjects;
		Queue<GameObject*> _destroyedObjects;

		Table<GameObject::ID, Entity*> _entities;
		Table<Component::ID, Component*> _components;

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
		static_assert(std::is_base_of<Component, T>::value, "You can only connect Component types");

		// Construct and initialize component
		auto& component = this->GetWorld().InitializeGameObject(New<T>());

		// Connect component
		component._entity = this;
		_components.Add(&component);
		component.Spawn();

		return component;
	}
}
