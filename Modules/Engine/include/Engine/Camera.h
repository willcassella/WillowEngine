// Camera.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "GameObject.h"

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

	Camera(const String& name = "", float vFOV = 43.f, float ratio = 1280.f / 720.f, float zMin = 0.1f, float zMax = 90.f);

	//////////////////
	///   Fields   ///
public:

	float VFOV;
	float Ratio;
	float ZMin;
	float ZMax;

	///////////////////
	///   Methods   ///
public:

	Mat4 GetPerspective() const;
};