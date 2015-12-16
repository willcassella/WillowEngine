// Component.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Reflection/ClassInfo.h>
#include "../include/Engine/GameObject.h"
#include "../include/Engine/Component.h"
#include "../include/Engine/World.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Component);

////////////////////////
///   Constructors   ///

Component::Component()
{
	_parent = nullptr;
	_owner = nullptr;
	_world = nullptr;
	_id = 0;
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
