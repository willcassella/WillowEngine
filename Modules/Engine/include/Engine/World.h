// World.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <memory>
#include <Core/Containers/Queue.h>
#include "GameObject.h"

/////////////////
///   Types   ///

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

	void Update();

	/** Spawns a new instance of the given GameObject type into the world at the start of the next frame.
	* Returns a reference to the GameObject. */
	template <class T>
	std::enable_if_t<std::is_base_of<GameObject, T>::value, T&> Spawn()
	{
		return static_cast<T&>(SpawnGameObject(New<T>()));
	}

	/** Spawns a new instance of the given Component type into the world at the start of the next frame.
	* Returns a reference to the new Component. */
	template <class T>
	std::enable_if_t<std::is_base_of<Component, T>::value, T&> Spawn()
	{
		return static_cast<T&>(SpawnComponent(New<T>()));
	}

	/** Spawns a new named GameObject of the given type at the start of the next frame. 
	* Returns a reference to the spawned GameObject. */
	template <class GameObjectT>
	GameObjectT& Spawn(String name)
	{
		static_assert(std::is_base_of<GameObject, GameObjectT>::value, "Only GameObjects may be given names.");

		// Create the object and set its name and ID
		UniquePtr<GameObjectT> object = New<GameObjectT>();
		object->_name = std::move(name);
		return static_cast<GameObjectT&>(Spawn(object.Transfer()));
	}

	template <class ComponentT>
	ComponentT* FindComponent(GHandle<ComponentT> handle)
	{
		return const_cast<ComponentT*>(const_self.FindComponent(handle));
	}

	template <class ComponentT>
	const ComponentT* FindComponent(GHandle<ComponentT> handle) const
	{
		const ComponentT* result = nullptr;
		_components.Find(handle.GetID(), [&result](const auto& c) { result = c.Get();});
		return result;
	}

	template <class GameObjectT>
	GameObjectT* FindGameObject(GHandle<GameObjectT> handle)
	{
		return const_cast<GameObjectT*>(const_self.FindGameObject(handle));
	}

	template <class GameObjectT>
	const GameObjectT* FindGameObject(GHandle<GameObjectT> handle)
	{
		const GameObjectT* result = nullptr;
		_gameObjects.Find(handle.GetID(), [&result](const auto& g) { result = g.Get(); });
		return result;
	}

	/** Returns an Array of the components of the given type in this World. */
	template <typename ComponentT>
	Array<const ComponentT*> GetComponentsOfType() const
	{
		Array<const ComponentT*> result;

		for (const auto& component : _components)
		{
			if (auto pComponent = Cast<ComponentT>(*component.Second))
			{
				result.Add(pComponent);
			}
		}

		return result;
	}

	/** Marks the given object for destruction. */
	void Destroy(GameObject& object);

	/** Marks the given object for destruction. */
	void Destroy(GHandle<GameObject> handle);

private:

	Component& SpawnComponent(UniquePtr<Component> component);

	GameObject& SpawnGameObject(UniquePtr<GameObject> gameObject);

	////////////////
	///   Data   ///
private:

	Table<GameObject::ID, UniquePtr<GameObject>> _gameObjects;
	Table<Component::ID, UniquePtr<Component>> _components;
	Queue<GameObject*> _destroyedObjects;
	Queue<GameObject*> _unspawnedObjects;
	GameObject::ID _nextGameObjectID;
	Component::ID _nextComponentID;
	std::unique_ptr<struct PhysicsData> _physicsData;
};

///////////////////
///   Methods   ///

template <class ComponentT>
ComponentT& GameObject::AddComponent()
{
	auto& component = GetWorld().Spawn<ComponentT>();
	AddComponent(component);

	return component;
}

template <class ComponentT>
ComponentT& GameObject::Attach()
{
	auto& component = GetWorld().Spawn<ComponentT>();
	Attach(component);

	return component;
}
