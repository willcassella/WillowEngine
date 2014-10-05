// StaticMeshComponent.cpp

#include "..\include\Core\StaticMeshComponent.h"
#include "..\include\Core\GameObject.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

StaticMeshComponent::StaticMeshComponent(GameObject& owner)
	: Super(owner)
{
	// Do nothing
}

///////////////////
///   Methods   ///

void StaticMeshComponent::OnRender(const Mat4& view, const Mat4& proj)
{
	if (Mesh.IsLoaded())
	{
		Mesh->Render(GetOwner().Transform.GetTransfomationMatrix(), view, proj);
	}
}