// GameObject.cpp

#include "..\include\Core\GameObject.h"
using namespace Willow;

GameObject::GameObject(const String& _name)
{
	this->name = _name;
}

GameObject::~GameObject()
{
	// Do nothing
}