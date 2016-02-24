// CameraComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Mat4.h>
#include "../Component.h"

namespace Willow
{
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

		/** The horizontal field of view of this Camera. */
		Angle Fov = 90.f;

		/** The screen ratio of this Camera. */
		float ScreenRatio = 16.f / 9;
		
		/** The distance to the near clipping plane. */
		float ZMin = 0.1f;

		/** The distance to the far clipping plane. */
		float ZMax = 100.f;

		///////////////////
		///   Methods   ///
	public:

		/** Generate a perspective projection matrix for this CameraComponent */
		FORCEINLINE Mat4 GetPerspective() const
		{
			return Mat4::PerspectiveHFOV(Fov, ScreenRatio, ZMin, ZMax);
		}
	};
}
