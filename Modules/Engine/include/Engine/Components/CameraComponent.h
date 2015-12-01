// CameraComponent.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Mat4.h>
#include "../Component.h"

class ENGINE_API CameraComponent : public Component
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Component)

	//////////////////
	///   Fields   ///
public:

	float HFov = 90.f;
	float VFov = 59.f;
	float ZMin = 0.1f;
	float ZMax = 100.f;

	///////////////////
	///   Methods   ///
public:

	/** Generate a perspective projection matrix for this CameraComponent */
	FORCEINLINE Mat4 GetPerspective() const
	{
		return Mat4::Perspective(HFov, VFov, ZMin, ZMax);
	}

	/** Sets the horizontal field of view with respect to the given vertical field of view and aspect ratio */
	FORCEINLINE void SetHFOV(float /*vFOV*/, float /*aspectRatio*/)
	{
		// @TODO: Implement this
	}

	/** Sets the vertical field of view with respect to the given horizontal field of view and aspect ratio */
	FORCEINLINE void SetVFOV(float /*hFOV*/, float /*aspectRatio*/)
	{
		// @TODO: Implement this
	}
};
