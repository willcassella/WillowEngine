// Prop.cpp

#include "..\include\Core\Prop.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

Prop::Prop(const String& name)
	: Super(name), MeshComponent(This)
{
	// Do nothing
}

///////////////////
///   Methods   ///

List<Component*> Prop::GetComponents()
{
	List<Component*> components = Super::GetComponents();
	components.Add(&MeshComponent);
	return components;
}