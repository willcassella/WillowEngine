// GameObject.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Engine/GameObject.h"
#include "../include/Engine/World.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(GameObject)
.Data("ID", &GameObject::_id)
.Data("World", &GameObject::_world)
.Data("Destroyed", &GameObject::_isDestroyed)
.Field("Name", &GameObject::_name, "The name of this GameObject.", FF_EditorOnly)
.Property("Destroyed", &GameObject::_isDestroyed, nullptr, "Whether this GameObject has been destroyed.");

////////////////////////
///   Constructors   ///

GameObject::GameObject()
{
	_hasSpawned = false;
	_world = nullptr;
	_rootComponent = nullptr;
	_id = 0;
	_isDestroyed = false;
}

///////////////////
///   Methods   ///

Component* GameObject::GetComponent(GHandle<Component> handle)
{
	return const_cast<Component*>(const_self.GetComponent(handle));
}

const Component* GameObject::GetComponent(GHandle<Component> handle) const
{
	const Component* result = nullptr;
	_components.Find(handle.GetID(), [&result](const auto& c) { result = c; });
	return result;
}

void GameObject::AddComponent(Component& component)
{
	assert(&component.GetWorld() == _world);

	_components[component.GetID()] = &component;
	component._owner = this;
}

void GameObject::AddComponent(GHandle<Component> handle)
{
	auto pComponent = GetWorld().FindComponent(handle);
	assert(pComponent);
	
	AddComponent(*pComponent);
}

void GameObject::Attach(Component& component)
{
	AddComponent(component);

	if (_rootComponent)
	{
		component.SetParent(_rootComponent);
	}
	else
	{
		_rootComponent = &component;
	}
}

void GameObject::Attach(GHandle<Component> handle)
{
	auto pComponent = GetWorld().FindComponent(handle);
	assert(pComponent);

	Attach(*pComponent);
}

void GameObject::RemoveComponent(Component& component)
{
	assert(&component.GetWorld() == _world);

	_components.Remove(component.GetID());
	component._owner = nullptr;
}

void GameObject::RemoveComponent(GHandle<Component> handle)
{
	auto pComponent = GetWorld().FindComponent(handle);
	assert(pComponent);

	RemoveComponent(*pComponent);
}

void GameObject::Detach(Component& component)
{
	RemoveComponent(component);
	component.SetParent(nullptr);
}

void GameObject::Detach(GHandle<Component> handle)
{
	auto pComponent = GetWorld().FindComponent(handle);
	assert(pComponent);

	Detach(*pComponent);
}

void GameObject::Destroy()
{
	GetWorld().Destroy(*this);
}

void GameObject::Build()
{
	// Do nothing
}

void GameObject::OnSpawn()
{
	// Do nothing
}

void GameObject::OnDestroy()
{
	// Do nothing
}
