// LightComponent.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Vec3.h>
#include "../Component.h"

/////////////////
///   Types   ///

enum class LightType : byte
{
	Point,
	Spot,
	Directional
};
REFLECTABLE_ENUM(LightType)

class ENGINE_API LightComponent : public Component
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Component)

	////////////////////////
	///   Constructors   ///
public:

	using Component::Component;

	//////////////////
	///   Fields   ///
public:

	/** The color of the light. */
	Vec3 Color = Vec3(1.f, 1.f, 1.f);
	
	/** The radius of this light. */
	float Radius = 10.f;

	/** The intensity of this light. */
	float Intensity = 1.f;

	/** The type of light this is. */
	LightType Type = LightType::Point;
};
