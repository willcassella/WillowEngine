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

	// @TODO: Rule of five
	GameObject(const String& name = "");
	~GameObject() override;

	//////////////////
	///   Fields   ///
public:

	String Name;
	Transform Transform;
	EventManager EventManager;

	///////////////////
	///   Methods   ///
public:

	Scene& GetScene();
	const Scene& GetScene() const;
	void Destroy();
	bool IsDestroyed() const;
	List<Component*> GetComponents() const;

	template <class ComponentType>
	ComponentType& AddComponent()
	{
		ComponentType* component = new ComponentType(This);
		_managedComponents.Add(component);
		return *component;
	}

	template <class ComponentType>
	List<ComponentType*> GetComponentsOfType()
	{
		List<ComponentType*> matches;

		for (auto& component : _components)
		{
			if (component->IsA<ComponentType>())
			{
				matches.Add((ComponentType*)component);
			}
		}

		return matches;
	}

protected:

	virtual void Update(float timeInterval);
	virtual void OnSpawn();
	virtual void OnDestroy();

	////////////////
	///   Data   ///
private:

	List<Component*> _components;
	List<Component*> _managedComponents;
	Scene* _scene;
	bool _isDestroyed;
};