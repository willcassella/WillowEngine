// GameObject.cpp

#include "..\include\Core\GameObject.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

GameObject::GameObject(const String& name)
{
	this->Name = name;
}

GameObject::~GameObject()
{
	// Do nothing
}

void GameObject::Tick(float timeInterval)
{
	// Do nothing
}