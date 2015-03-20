// Ghost.cpp

#include "..\include\ExampleGame\Ghost.h"
using namespace ExampleGame;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(ExampleGame::Ghost)
HAS_FACTORY
END_REFLECTION_INFO

////////////////////////
///   Constructors   ///

Ghost::Ghost()
	: MeshComponent(This), Slider(This)
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