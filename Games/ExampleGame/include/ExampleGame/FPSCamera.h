// FPSCamera.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/GameObjects/Camera.h>
#include "config.h"

class EXAMPLEGAME_API FPSCamera : public Camera
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Camera)

	///////////////////
	///   Methods   ///
public:

	void OnSpawn() override;

	///////////////////
	///   Actions   ///
public:

	void Move(Vec2 direction);
	void Look(Vec2 direction);
	void Click();
};
