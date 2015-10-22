// Light.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../GameObject.h"
#include "../Components/LightComponent.h"

class ENGINE_API Light : public GameObject
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(GameObject)

	////////////////////////
	///   Constructors   ///
public:

	Light(Scene& scene);

	//////////////////
	///   Fields   ///
public:

	UniquePtr<class LightComponent> LightComponent;
};
