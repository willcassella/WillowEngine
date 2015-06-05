// GameObject.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Engine/GameObject.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(GameObject)
.AddField("Name", &GameObject::_name) // @TODO: Register this differently?
.AddField("Transform", &GameObject::Transform);

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