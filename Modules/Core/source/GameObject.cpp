// GameObject.cpp

#include <map>
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

//void GameObject::BindAction(const String& action, ActionHandler handler)
//{
//	
//}