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

	Scalar HFov = 90.f;
	Scalar VFov = 59.f;
	Scalar ZMin = 0.1f;
	Scalar ZMax = 100.f;

	///////////////////
	///   Methods   ///
public:

	/** Generate a perspective projection matrix for this CameraComponent */
	FORCEINLINE Mat4 GetPerspective() const
	{
		return Mat4::Perspective(HFov, VFov, ZMin, ZMax);
	}

	/** Sets the horizontal field of view with respect to the given vertical field of view and aspect ratio */
	FORCEINLINE void SetHFOV(Scalar /*vFOV*/, Scalar /*aspectRatio*/)
	{
		// @TODO: Implement this
	}

	/** Sets the vertical field of view with respect to the given horizontal field of view and aspect ratio */
	FORCEINLINE void SetVFOV(Scalar /*hFOV*/, Scalar /*aspectRatio*/)
	{
		// @TODO: Implement this
	}
};
