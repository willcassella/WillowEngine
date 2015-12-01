// Ghost.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/GameObject.h>
#include <Engine/Components/StaticMeshComponent.h>

class EXAMPLEGAME_API Ghost : public GameObject
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(GameObject)

	//////////////////////
	///   Components   ///
public:

	GHandle<StaticMeshComponent> MeshComponent;

	///////////////////
	///   Methods   ///
public:

	void OnSpawn() const;

	///////////////////
	///   Actions   ///
public:

	void Disappear();
	void Spin(float value);
};