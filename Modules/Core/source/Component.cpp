// Component.cpp

#include "..\include\Core\GameObject.h"
#include "..\include\Core\Component.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

Component::Component(GameObject& owner)
	: _owner(owner)
{
	// All done
}

///////////////////
///   Methods   ///

GameObject& Component::GetOwner()
{
	return _owner;
}

const GameObject& Component::GetOwner() const
{
	return _owner;
}

void Component::OnSceneUpdate(float timeInterval)
{
	// Do nothing
}

void Component::OnRender(const Mat4& view, const Mat4& proj)
{
	// Do nothing
}