// Pawn.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "CameraComponent.h"

class ENGINE_API Pawn : public GameObject
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(GameObject);

	////////////////////////
	///   Constructors   ///
public:

	Pawn(const String& name = "");

	////////////////////
	////   Methods   ///
public:

	virtual const CameraComponent& GetView() const;
};