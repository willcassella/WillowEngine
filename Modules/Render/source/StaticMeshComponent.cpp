// StaticMeshComponent.cpp

#include "..\include\Render\StaticMeshComponent.h"
#include <Core\GameObject.h>
using namespace Willow;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(Willow::StaticMeshComponent)
FIELD(Mesh)
END_REFLECTION_INFO

////////////////////////
///   Constructors   ///

StaticMeshComponent::StaticMeshComponent(GameObject& owner)
	: Super(owner)
{
	// Do nothing
}

///////////////////
///   Methods   ///

void StaticMeshComponent::Render(const Mat4& view, const Mat4& proj)
{
	if (Mesh.IsLoaded())
	{
		Mesh->Render(GetOwner().Transform.GetTransfomationMatrix(), view, proj);
	}
}