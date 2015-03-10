// GameObject.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "EventManager.h"
#include "Transform.h"
#include "Component.h"

class ENGINE_API GameObject : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Object);
	friend Scene;
	friend Component;

	////////////////////////
	///   Constructors   ///
public:

	GameObject(const String& name = "");
	GameObject(const GameObject& copy) = delete;
	GameObject(GameObject&& move) = delete;
	~GameObject() override;

	//////////////////
	///   Fields   ///
public:

	Transform Transform;
	EventManager EventManager;

	///////////////////
	///   Methods   ///
public:

	/** Returns the name of this GameObject */
	FORCEINLINE const String& GetName() const
	{
		return _name;
	}

	/** Returns whether this GameObject will be destroyed at the end of the scene update */
	FORCEINLINE bool IsDestroyed() const
	{
		return _isDestroyed;
	}

	/** Returns a collection of all the Components attached to this GameObject */
	FORCEINLINE const Array<Component*>& GetComponents()
	{
		return _components;
	}

	/** Returns a collection of the Components attached to this GameObject */
	FORCEINLINE Array<const Component*> GetComponents() const
	{
		return Array<const Component*>(_components.CArray(), _components.Size());
	}

	/** Returns a collection of Components of the specified type attached to this GameObject */
	template <class ComponentType>
	Array<ComponentType*> GetComponentsOfType()
	{
		Array<ComponentType*> matches;

		for (Component* component : _components)
		{
			ComponentType* castedComponent = Cast<ComponentType>(*component);

			if (castedComponent)
			{
				matches.Add(castedComponent);
			}
		}

		return matches;
	}

	/** Returns a collection of Components of the specified type attached to this GameObject */
	template <class ComponentType>
	Array<const ComponentType*> GetComponentsOfType() const
	{
		Array<ComponentType*> matches;

		for (Component* component : _components)
		{
			ComponentType* castedComponent = Cast<ComponentType>(*component);

			if (castedComponent)
			{
				matches.Add(castedComponent);
			}
		}

		return matches;
	}

	/** Adds a Component of the specified type to this GameObject */
	template <class ComponentType>
	ComponentType& AddComponent()
	{
		ComponentType* component = new ComponentType(This);
		_managedComponent.Add(component);
		return *component;
	}

	/** Initiates the destruction procedure for this GameObject */
	void Destroy();

protected:

	/** Updates the state of this GameObject (called once per scene update) */
	virtual void Update(float timeInterval);

	/** Behavior for this GameObject upon spawning */
	virtual void OnSpawn();

	/** Behavior for this GameObject upon removal from scene */
	virtual void OnDestroy();

	/////////////////////
	///   Operators   ///
public:

	GameObject& operator=(const GameObject& copy) = delete;
	GameObject& operator=(GameObject&& move) = delete;

	////////////////
	///   Data   ///
private:

	String _name;
	bool _isDestroyed;
	Array<Component*> _managedComponent;
	Array<Component*> _components;
};