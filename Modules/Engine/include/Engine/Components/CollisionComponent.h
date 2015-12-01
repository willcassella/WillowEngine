// CollisionComponent.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Component.h"

/////////////////
///   Types   ///

enum class CollisionPrimitive : byte
{
	Sphere,
	Box,
	Capsule,
};
REFLECTABLE_ENUM(CollisionPrimitive);

class ENGINE_API CollisionComponent final : public Component
{
	////////////////////////
	///   Constructors   ///
public:

	CollisionComponent(GameObject& owner);

	//////////////////
	///   Fields   ///
public:

	/** Which primitive to use for this CollisonComponent. */
	CollisionPrimitive Primitive;

	/** */
	uint32 Size;
};
