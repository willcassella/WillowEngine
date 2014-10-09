// SlideComponent.cpp

#include "..\include\ExampleGame\SlideComponent.h"
using namespace ExampleGame;

////////////////////////
///   Constructors   ///

SlideComponent::SlideComponent(Willow::GameObject& owner)
	: Super(owner)
{
	// All done
}

///////////////////
///   Methods   ///

void SlideComponent::OnSceneUpdate(float timeInterval)
{
	this->GetOwner().Transform.Translate(Willow::Vec3(0.001f));
}