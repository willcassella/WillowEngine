// StaticMeshComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../../Component.h"
#include "../../Resources/StaticMesh.h"
#include "../../Resources/Material.h"

namespace willow
{
	class ENGINE_API StaticMeshComponent final : public Component
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Component)

		////////////////////////
		///   Constructors   ///
	public:

		StaticMeshComponent();

		//////////////////
		///   Fields   ///
	public:

		/** Whether this mesh is visible. */
		bool visible = true;

		/** The Static Mesh used. */
		ResourceHandle<StaticMesh> mesh;

		/** The material applied to the StaticMesh. 
		* TODO: This is unbeleivably broken right now, need to fix. */
		ResourceHandle<Material> material;

		/** The material parameters specific to this instance. */
		Material::ParamTable instance_params;
	};
}
