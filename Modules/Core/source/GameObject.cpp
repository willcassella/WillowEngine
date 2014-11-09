// GameObject.cpp

#include "..\include\Core\GameObject.h"
using namespace Willow;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(Willow::GameObject)
HAS_FACTORY
FIELD(Name)
FIELD(Transform)
END_REFLECTION_INFO

////////////////////////
///   Constructors   ///

GameObject::GameObject(const String& name)
	: Name(name)
{
	this->_scene = nullptr;
	this->_isDestroyed = false;
}

GameObject::~GameObject()
{
	for (auto& component : _managedComponents)
	{
		delete component;
	}
}

///////////////////
///   Methods   ///

Scene& GameObject::GetScene()
{
	if (_scene)
	{
		return *_scene;
	}
	else
	{
		throw String("GameObject is not associated with a scene");
	}
}

const Scene& GameObject::GetScene() const
{
	if (_scene)
	{
		return *_scene;
	}
	else
	{
		throw String("GameObject is not associated with a scene");
	}
}

void GameObject::Destroy()
{
	this->OnDestroy();
	_isDestroyed = true;
}

bool GameObject::IsDestroyed() const
{
	return _isDestroyed;
}

List<Component*> GameObject::GetComponents() const
{
	return _components;
}

void GameObject::Update(float timeInterval)
{
	// Do nothing
}

void GameObject::OnDestroy()
{
	// Do nothing
}