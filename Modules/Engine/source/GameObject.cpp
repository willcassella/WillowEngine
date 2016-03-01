// GameObject.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/Umbrellas/Reflection.h>
#include "../include/Engine/GameObject.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::GameObject)
.Data("ID", &GameObject::_id)
.Property("ID", &GameObject::GetID, nullptr, "Unique ID")
.Property("Location", &GameObject::GetLocation, &GameObject::SetLocation, "Location in local space", "Transform")
.Property("World Location", &GameObject::GetWorldLocation, &GameObject::SetWorldLocation, "Location in world space", "Transform")
.Property("Rotation", &GameObject::GetRotation, &GameObject::SetRotation, "Rotation in local space", "Transform")
.Property("World Rotation", &GameObject::GetWorldRotation, &GameObject::SetWorldRotation, "Rotation in world space", "Transform")
.Property("Scale", &GameObject::GetScale, &GameObject::SetScale, "Scale", "Transform");

BUILD_ENUM_REFLECTION(Willow::GameObject::State)
.Value("Uninitialized", Willow::GameObject::State::Uninitialized)
.Value("Spawned", Willow::GameObject::State::Spawned)
.Value("Destroyed", Willow::GameObject::State::Destroyed);

namespace Willow
{
	///////////////////
	///   Methods   ///

	void GameObject::Destroy()
	{
		assert(_state >= State::Spawned);

		if (this->IsDestroyed())
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
}
