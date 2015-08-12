// StaticMeshComponent.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Resource/AssetPtr.h>
#include "../Component.h"
#include "../Assets/StaticMesh.h"

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

	using Component::Component;

	//////////////////
	///   Fields   ///
public:

	AssetPtr<StaticMesh> Mesh;
};
