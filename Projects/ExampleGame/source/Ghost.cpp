// Ghost.cpp

#include "..\include\ExampleGame\Ghost.h"
using namespace ExampleGame;

////////////////////////
///   Constructors   ///

Ghost::Ghost(const Willow::String& name)
	: Super(name), MeshComponent(This), Slider(This)
{
	EventManager.BindAction("Poof", this, &Ghost::Disappear);
	EventManager.BindAxis("Spin", this, &Ghost::Spin);
	hasDisappeared = false;
}

///////////////////
///   Actions   ///

void Ghost::Disappear()
{
	if (!hasDisappeared)
	{
		MeshComponent.Disable();
		hasDisappeared = true;
	}
	else
	{
		MeshComponent.Enable();
		hasDisappeared = false;
	}
}

void Ghost::Spin(float value)
{
	Transform.Rotate(Willow::Vec3::Up, value);
}