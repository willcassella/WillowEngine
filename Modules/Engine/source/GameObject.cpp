// GameObject.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Engine/GameObject.h"
#include "../include/Engine/Scene.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(GameObject)
.Data("ID", &GameObject::_id)
.Data("Scene", &GameObject::_scene)
.Data("Alive", &GameObject::_isAlive)
.Data("Destroyed", &GameObject::_isDestroyed)
.Field("Name", &GameObject::_name, "The name of this GameObject.")
.Field("Transform", &GameObject::Transform, "The world transformation of this GameObject.")
.Property("Destroyed", &GameObject::_isDestroyed, nullptr, "Whether this GameObject has been destroyed.");

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
