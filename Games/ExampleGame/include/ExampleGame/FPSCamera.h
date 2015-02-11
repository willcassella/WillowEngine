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

	FPSCamera(const String& name = "", float vFOV = 43.f, float ratio = 1280.f / 720.f, float zMin = 0.1f, float zMax = 90.f);

	///////////////////
	///   Actions   ///
public:

	void MoveForward(float value);
	void MoveRight(float value);
	void LookUp(float value);
	void LookRight(float value);
};