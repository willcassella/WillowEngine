// StaticMeshComponent.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Resource/AssetPtr.h>
#include "../Component.h"
#include "../Assets/StaticMesh.h"
#include "../Assets/Material.h"

class ENGINE_API StaticMeshComponent final : public Component
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Component)

	//////////////////
	///   Fields   ///
public:

	/** Whether this mesh is visible. */
	bool Visible = true;

	/** The Static Mesh used. */
	AssetPtr<StaticMesh> Mesh;

	/** The material applied to the StaticMesh. */
	AssetPtr<class Material> Material;

	/** The material parameters specific to this instance. */
	Table<String, ::Material::Param> InstanceParams;
};
