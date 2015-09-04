// Ghost.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

//#include <Engine/StaticMeshComponent.h>
#include <Engine/GameObject.h>
#include <Engine/Components/StaticMeshComponent.h>
#include "SlideComponent.h"

class EXAMPLEGAME_API Ghost : public GameObject
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(GameObject)

	/////////////////////////
	///   Constructors   ///
public:

	Ghost(Scene& scene);

	//////////////////////
	///   Components   ///
public:

	UniquePtr<StaticMeshComponent> MeshComponent;
	UniquePtr<SlideComponent> Slider;

	///////////////////
	///   Actions   ///
public:

	void Disappear();
	void Spin(float value);

	////////////////
	///   Data   ///
protected:

	bool hasDisappeared;
};