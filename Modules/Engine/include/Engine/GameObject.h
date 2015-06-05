// GameObject.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

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

	GameObject(Scene& scene);
	GameObject(const GameObject& copy) = delete;
	GameObject(GameObject&& move) = delete;

	//////////////////
	///   Fields   ///
public:

	Transform Transform;

	///////////////////
	///   Methods   ///
public:

	/** Returns the name of this GameObject */
	FORCEINLINE const String& GetName() const &
	{
		return _name;
	}

	/** Returns the name of this GameObject */
	FORCEINLINE String GetName() &&
	{
		return _name;
	}

	/** Sets the name of this GameObject */
	FORCEINLINE void SetName(const String& name)
	{
		_name = name;
	}

	/** Returns whether this GameObject is alive (if not, it is either destroyed or not yet spawned) */
	FORCEINLINE bool IsAlive() const
	{
		return _isAlive;
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

	/** Initiates the destruction procedure for this GameObject */
	void Destroy();

protected:

	/** Behavior for this GameObject upon spawning */
	virtual void OnSpawn();

	/** Behavior for this GameObject upon destruction */
	virtual void OnDestroy();

	/////////////////////
	///   Operators   ///
public:

	GameObject& operator=(const GameObject& copy) = delete;
	GameObject& operator=(GameObject&& move) = delete;

	////////////////
	///   Data   ///
private:

	Array<Component*> _components;
	String _name;
	uint32 _id;
	bool _isAlive;
	bool _isDestroyed;
};