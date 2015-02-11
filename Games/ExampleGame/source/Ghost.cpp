// Ghost.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "..\include\ExampleGame\Ghost.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Ghost);

////////////////////////
///   Constructors   ///

Ghost::Ghost(const String& name)
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
	Transform.Rotate(Vec3::Up, value);
}