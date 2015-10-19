// Prop.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../GameObject.h"
#include "../Components/StaticMeshComponent.h"

class ENGINE_API Prop final : public GameObject
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(GameObject)

	////////////////////////
	///   Constructors   ///
public:

	Prop(Scene& scene);

	//////////////////
	///   Fields   ///
public:

	UniquePtr<StaticMeshComponent> MeshComponent;
};
