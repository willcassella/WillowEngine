// Component.h
#pragma once

#include <Utility\ResourcePtr.h>
#include <Core\Component.h>
#include "StaticMesh.h"

namespace Willow
{
	class RENDER_API StaticMeshComponent : public Component
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(Component)

		//////////////////
		///   Fields   ///
	public:

		ResourcePtr<StaticMesh> Mesh;

		////////////////////////
		///   Constructors   ///
	public:
		
		StaticMeshComponent(GameObject& owner);

		///////////////////
		///   Methods   ///
	protected:

		void Render(const Mat4& view, const Mat4& proj) override;
	};
}