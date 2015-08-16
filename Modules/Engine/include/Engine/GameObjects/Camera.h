// Camera.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../GameObject.h"
#include "../Components/CameraComponent.h"

class ENGINE_API Camera : public GameObject
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(GameObject)

	////////////////////////
	///   Constructors   ///
public:

	Camera(Scene& scene);

	//////////////////////
	///   Components   ///
public:

	UniquePtr<CameraComponent> Lens;

	///////////////////
	///   Methods   ///
public:

	FORCEINLINE Mat4 GetPerspective() const
	{
		return Lens->GetPerspective();
	}
};