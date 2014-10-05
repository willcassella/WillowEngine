// GameObject.cpp

#include "..\include\Core\GameObject.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

GameObject::GameObject(const String& name)
	: Name(name)
{
	this->_scene = nullptr;
	this->_isDestroyed = false;
}

Scene& GameObject::GetScene()
{
	assert(_scene);
	return *_scene;
}

const Scene& GameObject::GetScene() const
{
	assert(_scene);
	return *_scene;
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

List<Component*> GameObject::GetComponents()
{
	// Base GameObject class has no components
	return List<Component*>();
}

void GameObject::Tick(float timeInterval)
{
	// Do nothing
}

void GameObject::OnDestroy()
{
	// Do nothing
}