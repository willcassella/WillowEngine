// GameObject.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Engine/GameObject.h"
#include "../include/Engine/Scene.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(GameObject)
.AddProperty("Name", "The name of this GameObject.", &GameObject::_name)
.AddProperty("Scene", "The scene this GameObject belongs to.", &GameObject::_scene, &GameObject::SetScene)
.AddProperty("Transform", "The world transformation of this GameObject.", &GameObject::Transform)
.AddProperty("ID", "The unique ID of this GameObject.", &GameObject::_id)
.AddProperty("Alive", "Whether this GameObject is alive.", &GameObject::_isAlive)
.AddProperty("Destroyed", "Whether this GameObject is destroyed.", &GameObject::_isDestroyed);

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
