// Component.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Engine/GameObject.h"
#include "../include/Engine/Component.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Component);

////////////////////////
///   Constructors   ///

Component::Component(GameObject& owner)
	: _owner(&owner)
{
	_owner->_components.Add(this);
	_isEnabled = false;
}

///////////////////
///   Methods   ///

bool Component::IsEnabled() const
{
	return _isEnabled;
}

void Component::Enable()
{
	if (!this->IsEnabled())
	{
		_isEnabled = true;
		this->OnEnabled();
	}
}

void Component::Disable()
{
	if (this->IsEnabled())
	{
		_isEnabled = false;
		this->OnDisabled();
	}
}

GameObject& Component::GetOwner()
{
	return *_owner;
}

const GameObject& Component::GetOwner() const
{
	return *_owner;
}

void Component::OnDisabled()
{
	// Do nothing
}

void Component::OnEnabled()
{
	// Do nothing
}