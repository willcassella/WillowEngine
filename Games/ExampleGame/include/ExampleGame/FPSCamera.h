// FPSCamera.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Camera.h>
#include "config.h"

class EXAMPLEGAME_API FPSCamera : public Camera
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Camera);

	////////////////////////
	///   Constructors   ///
public:

	FPSCamera(Scene& scene);

	///////////////////
	///   Actions   ///
public:

	void MoveForward(float value);
	void MoveRight(float value);
	void LookUp(float value);
	void LookRight(float value);
};