// Pawn.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../GameObject.h"
#include "../Components/CameraComponent.h"

class ENGINE_API Pawn : public GameObject
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(GameObject)

	////////////////////////
	///   Constructors   ///
public:

	Pawn(Scene& scene);

	////////////////////
	////   Methods   ///
public:

	/** Returns a camera component representing this Pawn's point of view */
	virtual const CameraComponent& GetView() const;

	////////////////
	///   Data   ///
private:

	CameraComponent _defaultCamera;
};