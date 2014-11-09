// Prop.cpp

#include "..\include\Render\Prop.h"
using namespace Willow;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(Willow::Prop)
HAS_FACTORY
FIELD(MeshComponent)
END_REFLECTION_INFO

////////////////////////
///   Constructors   ///

Prop::Prop(const String& name)
	: Super(name), MeshComponent(This)
{
	// Do nothing
}