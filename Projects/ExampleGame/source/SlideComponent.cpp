// SlideComponent.cpp

#include "..\include\ExampleGame\SlideComponent.h"
using namespace ExampleGame;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(ExampleGame::SlideComponent)
END_REFLECTION_INFO

////////////////////////
///   Constructors   ///

SlideComponent::SlideComponent(Willow::GameObject& owner)
	: Super(owner)
{
	// All done
}

///////////////////
///   Methods   ///

void SlideComponent::Update(float timeInterval)
{
	this->GetOwner().Transform.Translate(Willow::Vec3(0.008f));
}