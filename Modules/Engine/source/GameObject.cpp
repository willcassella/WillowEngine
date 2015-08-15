// GameObject.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Engine/GameObject.h"
#include "../include/Engine/Scene.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(GameObject)
.AddProperty("Name", "", &GameObject::GetName, &GameObject::SetName)
.AddProperty("Scene", "", &GameObject::_scene, &GameObject::SetScene, PF_Set_SerializeOnly)
.AddProperty("Transform", "", &GameObject::Transform)
.AddProperty("ID", "", &GameObject::_id)
.AddProperty("Alive", "", &GameObject::_isAlive)
.AddProperty("Destroyed", "", &GameObject::_isDestroyed);

////////////////////////
///   Constructors   ///

GameObject::GameObject(Scene& scene)
	: _scene(&scene)
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

void GameObject::SetScene(Scene* scene)
{
	// TODO: This needs work
	_scene = scene;
}
