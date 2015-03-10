// GameObject.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Engine/GameObject.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(GameObject)
.AddField("Name", &GameObject::_name) // @TODO: Register this differently?
.AddField("Transform", &GameObject::Transform);

////////////////////////
///   Constructors   ///

GameObject::GameObject(const String& name)
	: _name(name), _isDestroyed(false), _components()
{
	// All done
}

GameObject::~GameObject()
{
	for (Component* component : _managedComponent)
	{
		delete component;
	}
}

///////////////////
///   Methods   ///

void GameObject::Destroy()
{
	this->OnDestroy();
	_isDestroyed = true;
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