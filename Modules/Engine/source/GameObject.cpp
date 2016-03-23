// GameObject.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/Umbrellas/Reflection.h>
#include "../include/Engine/GameObject.h"
#include "../include/Engine/World.h"

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
.Value("Spawning", Willow::GameObject::State::Spawning)
.Value("Spawned", Willow::GameObject::State::Spawned)
.Value("Destroyed", Willow::GameObject::State::Destroyed);

namespace Willow
{
	///////////////////
	///   Methods   ///

	void GameObject::ToArchive(ArchiveWriter& writer) const
	{
		Operations::Default::ToArchive(*this, writer);
	}

	void GameObject::FromArchive(const ArchiveReader& reader)
	{
		Operations::Default::FromArchive(*this, reader);
	}

	void GameObject::Destroy()
	{
		this->GetWorld().DestroyGameObject(*this);
	}

	void GameObject::OnSpawn()
	{
		// Do nothing
	}

	void GameObject::OnClone(GameObject& clone, World& world)
	{
		// Do nothing
	}

	void GameObject::OnDestroy()
	{
		// Do nothing
	}

	Owned<GameObject> GameObject::Clone(World& world) const
	{
		return nullptr; // TODO: Implement this
	}
}
