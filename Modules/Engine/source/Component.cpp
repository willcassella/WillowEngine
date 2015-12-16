// Component.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Reflection/ClassInfo.h>
#include "../include/Engine/GameObject.h"
#include "../include/Engine/Component.h"
#include "../include/Engine/World.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Component)
.Data("Owner", &Component::_owner)
.Data("World", &Component::_world)
.Data("ID", &Component::_id)
.Data("Status", &Component::_status)
.Data("Transform", &Component::_transform)
.Data("Parent", &Component::_parent)
.Data("Children", &Component::_children);

BUILD_ENUM_REFLECTION(Component::Status)
.Value("Uninitialized", Component::Status::Uninitialized, "This Component has not yet been initialized.")
.Value("Initializing", Component::Status::Initializing, "This Component is currently initializing.")
.Value("Initialized", Component::Status::Initialized, "This Component has successfully been Initialized.");

////////////////////////
///   Constructors   ///

Component::Component()
{
	_parent = nullptr;
	_owner = nullptr;
	_world = nullptr;
	_id = 0;
	_status = Status::Uninitialized;
}

Component::~Component()
{
	for (auto child : _children)
	{
		child->_parent = nullptr;
	}
}

///////////////////
///   Methods   ///

bool Component::IsParentedTo(const Component& component) const
{
	// If this Component has no parent
	if (!_parent)
	{
		return false;
	}

	return _parent == &component || _parent->IsParentedTo(component);
}

void Component::SetParent(Component* parent)
{
	// If we're already parented to that object
	if (_parent == parent)
	{
		return;
	}

	// If we're currently parented to something
	if (_parent)
	{
		_parent->_children.DeleteFirst(this);
	}

	// If we're being parented to something
	if (parent)
	{
		assert(parent != this && !this->IsParentedTo(*parent));
		parent->_children.Add(this);
	}

	_parent = parent;
}

Mat4 Component::GetTransformationMatrix() const
{
	if (_parent)
	{
		return _parent->GetTransformationMatrix() * _transform.GetMatrix();
	}
	else
	{
		return _transform.GetMatrix();
	}
}

void Component::OnInitialize()
{
	assert(_status == Status::Initializing /* You may not call 'Component::OnInitialize' before or after a Component has begun Initialization. */);
}

void Component::Initialize(World& world)
{
	assert(_status == Status::Uninitialized /* You may not call 'Component::Initialize' after a Component has begun Initialization. */);
	_world = &world;

	_status = Status::Initializing;
	this->OnInitialize();
	_status = Status::Initialized;
}
