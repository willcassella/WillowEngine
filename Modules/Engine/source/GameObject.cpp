// GameObject.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/Umbrellas/Reflection.h>
#include "../include/Engine/GameObject.h"
#include "../include/Engine/World.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::GameObject)
.Data("id", &GameObject::_id)
.Data("world", &GameObject::_world, DF_Transient)
.Property("id", &GameObject::get_id, nullptr)
.Property("state", &GameObject::get_state, nullptr);

BUILD_ENUM_REFLECTION(willow::GameObject::State)
.Value("Uninitialized", willow::GameObject::State::Uninitialized)
.Value("Spawning", willow::GameObject::State::Spawning)
.Value("Spawned", willow::GameObject::State::Spawned)
.Value("Destroyed", willow::GameObject::State::Destroyed);

namespace willow
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

	void GameObject::destroy()
	{
		this->get_world().destroy_object(*this);
	}

	void GameObject::on_initialize()
	{
		// Do nothing
	}

	void GameObject::on_spawn()
	{
		// Do nothing
	}

	void GameObject::on_clone(const GameObject& /*old*/)
	{
		// Do nothing
	}

	void GameObject::on_destroy()
	{
		// Do nothing
	}

	/////////////////////
	///   Operators   ///

	GameObject& GameObject::operator=(const GameObject& /*copy*/)
	{
		// Do nothing (id, world, and state are not copied)
		return *this;
	}
}
