// SlideComponent.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Engine/GameObject.h>
#include "..\include\ExampleGame\SlideComponent.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(SlideComponent);

////////////////////////
///   Constructors   ///

SlideComponent::SlideComponent(GameObject& owner)
	: Super(owner)
{
	// All done
}

///////////////////
///   Methods   ///

void SlideComponent::Update(float timeInterval)
{
	GetOwner().Transform.Translate(Vec3(0.008f));
}