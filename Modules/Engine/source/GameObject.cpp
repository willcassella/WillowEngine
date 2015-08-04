// GameObject.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Engine/GameObject.h"
#include "../include/Engine/Scene.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(GameObject)
.AddProperty("Name", "", &GameObject::GetName, &GameObject::SetName)
.AddProperty("Scene", "", &GameObject::GetScene, nullptr)
.AddProperty("Transform", "", &GameObject::Transform)
.AddProperty("ID", "", &GameObject::_id, nullptr)
.AddProperty("Alive", "", &GameObject::_isAlive, nullptr)
.AddProperty("Destroyed", "", &GameObject::_isDestroyed, nullptr);

////////////////////////
///   Constructors   ///

GameObject::GameObject(Scene& scene)
{
	_isDestroyed = false;
}

///////////////////
///   Methods   ///

void GameObject::Destroy()
{
	OnDestroy();
	_isDestroyed = true;
}

void GameObject::OnDestroy()
{
	// Do nothing
}

void GameObject::OnSpawn()
{
	// Do nothing
}