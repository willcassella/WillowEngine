// SlideComponent.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Engine/GameObject.h>
#include <Engine/Scene.h>
#include "../include/ExampleGame/SlideComponent.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(SlideComponent);

////////////////////////
///   Constructors   ///

SlideComponent::SlideComponent(GameObject& owner)
	: Base(owner)
{
	owner.GetScene().Events.Bind("Update", self, &SlideComponent::OnUpdate);
}

///////////////////
///   Methods   ///

void SlideComponent::OnUpdate(float /*timeInterval*/)
{
	GetOwner().Transform.Translate(Vec3{ 0.008f, 0.f, 0.f });
}