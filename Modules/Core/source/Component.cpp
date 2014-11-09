// Component.cpp

#include "..\include\Core\GameObject.h"
#include "..\include\Core\Component.h"
using namespace Willow;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(Willow::Component)
END_REFLECTION_INFO

////////////////////////
///   Constructors   ///

Component::Component(GameObject& owner)
	: _owner(&owner)
{
	_owner->_components.Add(this);
	_isEnabled = true;
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
		this->GetOwner()._components.Add(this);
		_isEnabled = true;
	}
}

void Component::Disable()
{
	if (this->IsEnabled())
	{
		this->GetOwner()._components.RemoveAll(this);
		_isEnabled = false;
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

void Component::Update(float timeInterval)
{
	// Do nothing
}

void Component::Render(const Mat4& view, const Mat4& proj)
{
	// Do nothing
}