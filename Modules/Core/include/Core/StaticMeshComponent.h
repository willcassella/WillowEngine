// Component.h
#pragma once

#include <Resource\ResourcePtr.h>
#include <Render\StaticMesh.h>
#include "Component.h"

namespace Willow
{
	class CORE_API StaticMeshComponent : public Component
	{
		///////////////////////
		///   Information   ///
	public:

		typedef Component Super;

		//////////////////
		///   Fields   ///
	public:

		ResourcePtr<StaticMesh> Mesh;

		////////////////////////
		///   Constructors   ///
	public:
		
		StaticMeshComponent(GameObject& owner);
		~StaticMeshComponent() override = default;

		///////////////////
		///   Methods   ///
	protected:

		void OnRender(const Mat4& view, const Mat4& proj) override;
	};
}