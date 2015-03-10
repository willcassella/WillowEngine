// Camera.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "GameObject.h"
#include "CameraComponent.h"

class ENGINE_API Camera : public GameObject
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(GameObject);

	////////////////////////
	///   Constructors   ///
public:

	Camera(const String& name = "");

	//////////////////////
	///   Components   ///
public:

	CameraComponent CameraComponent;

	///////////////////
	///   Methods   ///
public:

	FORCEINLINE Mat4 GetPerspective() const
	{
		return CameraComponent.GetPerspective();
	}
};