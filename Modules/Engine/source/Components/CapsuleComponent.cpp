// CapsuleComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Engine/World.h"
#include "../../include/Engine/Components/CapsuleComponent.h"
#include "../Physics.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(CapsuleComponent);

////////////////////////
///   Constructors   ///

CapsuleComponent::CapsuleComponent()
{
	_shape = std::make_unique<btCapsuleShape>(Scalar{ 5 }, Scalar{ 5 });
}

CapsuleComponent::~CapsuleComponent()
{
	// All done
}

///////////////////
///   Methods   ///

btCollisionShape* CapsuleComponent::GetShape()
{
	// Create capsule shape
	return _shape.get();
}
