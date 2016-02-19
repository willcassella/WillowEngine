// FPSCharacter.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Memory/Pointers/Weak.h>
#include <Engine/Components/CameraComponent.h>
#include <Engine/Components/CapsuleComponent.h>
#include "config.h"

class EXAMPLEGAME_API FPSCharacter : public Entity
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Entity)

	//////////////////////
	///   Components   ///
public:

	Weak<CameraComponent> View;
	Weak<CapsuleComponent> Capsule;

	///////////////////
	///   Methods   ///
protected:

	void OnSpawn() override;

	///////////////////
	///   Actions   ///
public:

	void Move(Vec2 direction);
	void Look(Vec2 direction);
	void Fire();
};
