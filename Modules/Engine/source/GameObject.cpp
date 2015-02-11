// GameObject.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "..\include\Engine\GameObject.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(GameObject)
.AddField("Name", &GameObject::Name)
.AddField("Transform", &GameObject::Transform);

////////////////////////
///   Constructors   ///

GameObject::GameObject(const String& name)
	: Name(name)
{
	this->_scene = nullptr;
	this->_isDestroyed = false;
}

GameObject::~GameObject()
{
	for (auto& component : _managedComponents)
	{
		delete component;
	}
}

///////////////////
///   Methods   ///

Scene& GameObject::GetScene()
{
	if (_scene)
	{
		return *_scene;
	}
	else
	{
		throw String("GameObject is not associated with a scene");
	}
}

const Scene& GameObject::GetScene() const
{
	if (_scene)
	{
		return *_scene;
	}
	else
	{
		throw String("GameObject is not associated with a scene");
	}
}

void GameObject::Destroy()
{
	this->OnDestroy();
	_isDestroyed = true;
}

bool GameObject::IsDestroyed() const
{
	return _isDestroyed;
}

List<Component*> GameObject::GetComponents() const
{
	return _components;
}

void GameObject::Update(float timeInterval)
{
	// Do nothing
}

void GameObject::OnDestroy()
{
	// Do nothing
}

void GameObject::OnSpawn()
{
	// Do nothing
}