// GameObject.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/Umbrellas/Reflection.h>
#include "../include/Engine/GameObject.h"
#include "../include/Engine/World.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::GameObject)
.Data("ID", &GameObject::_id)
.Data("World", &GameObject::_world, DF_Transient)
.Property("ID", &GameObject::GetID, nullptr)
.Property("State", &GameObject::GetState, nullptr)
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
	////////////////////////
	///   Constructors   ///

	GameObject::GameObject()
		: _id{ 0 }, 
		_world{ nullptr },
		_state { State::Uninitialized }
	{
		// All done
	}

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

	void GameObject::OnInitialize()
	{
		// Do nothing
	}

	void GameObject::OnSpawn()
	{
		// Do nothing
	}

	void GameObject::OnClone(const GameObject& /*old*/)
	{
		// Do nothing
	}

	void GameObject::OnDestroy()
	{
		// Do nothing
	}

	/////////////////////
	///   Operators   ///

	GameObject& GameObject::operator=(const GameObject& /*copy*/)
	{
		// Do nothing (ID and State are not copied)
		return *this;
	}
}
