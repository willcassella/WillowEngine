// GameObject.cpp

#include <map>
#include "..\include\Core\GameObject.h"
#include "..\include\Core\Game.h"
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