// FPSCharacter.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Engine/World.h>
#include "../include/ExampleGame/FPSCharacter.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(FPSCharacter)
.Field("View", &FPSCharacter::View, "")
.Field("Capsule", &FPSCharacter::Capsule, "");

///////////////////
///   Methods   ///

void FPSCharacter::OnSpawn()
{
	Base::OnSpawn();

	Capsule = &this->Connect<CapsuleComponent>();
	View = &this->Attach<CameraComponent>();

	GetWorld().Events.Bind("Move", *this, &FPSCharacter::Move);
	GetWorld().Events.Bind("Look", *this, &FPSCharacter::Look);
	GetWorld().Events.Bind("Click", *this, &FPSCharacter::Fire);
}

///////////////////
///   Actions   ///

void FPSCharacter::Move(Vec2 direction)
{
	this->Translate(Vec3(direction.X, 0, -direction.Y)/10);
}

void FPSCharacter::Look(Vec2 direction)
{
	this->RotateGlobal(Vec3::Up, direction.X);
	this->Rotate(Vec3::Right, direction.Y);
}

void FPSCharacter::Fire()
{
	// Spawn something
}
