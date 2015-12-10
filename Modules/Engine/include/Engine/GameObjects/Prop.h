// Prop.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../GameObject.h"
#include "../Components/StaticMeshComponent.h"

class ENGINE_API Prop : public GameObject
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(GameObject)

	//////////////////
	///   Fields   ///
public:

	GHandle<StaticMeshComponent> MeshComponent;

	///////////////////
	///   Methods   ///
protected:

	void Build() override;
};
