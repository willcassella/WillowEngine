// CameraComponent.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Math/Mat4.h>
#include "Component.h"

class ENGINE_API CameraComponent : public Component
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Component);

	////////////////////////
	///   Constructors   ///
public:

	CameraComponent(GameObject& owner);

	//////////////////
	///   Fields   ///
public:

	float HFOV = 90.f;
	float VFOV = 59.f;
	float ZMin = 0.1f;
	float ZMax = 100.f;

	///////////////////
	///   Methods   ///
public:

	/** Generate a perspective projection matrix for this CameraComponent */
	FORCEINLINE Mat4 GetPerspective() const
	{
		return Mat4::Perspective(HFOV, VFOV, ZMin, ZMax);
	}

	/** Sets the horizontal field of view with respect to the given vertical field of view and aspect ratio */
	FORCEINLINE void SetHFOV(float vFOV, float aspectRatio)
	{
		// @TODO: Implement this
	}

	/** Sets the vertical field of view with respect to the given horizontal field of view and aspect ratio */
	FORCEINLINE void SetVFOV(float hFOV, float aspectRatio)
	{
		// @TODO: Implement this
	}
};