// GameObject.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Engine/GameObject.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(GameObject)
.Data("ID", &GameObject::_id)
.Data("State", &GameObject::_state)
.Property("ID", &GameObject::GetID, nullptr, "Unique ID")
.Property("State", &GameObject::GetState, nullptr, "State of GameObject")
.Property("Location", &GameObject::GetLocation, &GameObject::SetLocation, "Location in local space", "Transform")
.Property("World Location", &GameObject::GetWorldLocation, &GameObject::SetWorldLocation, "Location in world space", "Transform")
.Property("Rotation", &GameObject::GetRotation, &GameObject::SetRotation, "Rotation in local space", "Transform")
.Property("World Rotation", &GameObject::GetWorldRotation, &GameObject::SetWorldRotation, "Rotation in world space", "Transform")
.Property("Scale", &GameObject::GetScale, &GameObject::SetScale, "Scale", "Transform");

BUILD_ENUM_REFLECTION(GameObject::State)
.Value("Uninitialized", GameObject::State::Uninitialized)
.Value("Initialized", GameObject::State::Initialized)
.Value("Spawning", GameObject::State::Spawning)
.Value("Spawned", GameObject::State::Spawned)
.Value("Destroyed", GameObject::State::Destroyed);

///////////////////
///   Methods   ///

void GameObject::Destroy()
{
	assert(this->GetState() >= State::Spawned);

	if (this->GetState() == State::Destroyed)
	{
		// We've already run the destruction procedure
		return;
	}
	else
	{
		_state = State::Destroyed;
		this->OnDestroy();
	}
}

void GameObject::OnSpawn()
{
	// Do nothing
}

void GameObject::OnDestroy()
{
	// Do nothing
}

void GameObject::Initialize(ID id)
{
	assert(this->GetState() == State::Uninitialized);

	_id = id;
	_state = State::Initialized;
}

void GameObject::Spawn()
{
	assert(this->GetState() == State::Initialized);

	_state = State::Spawning;
	this->OnSpawn();
	_state = State::Spawned;
}
