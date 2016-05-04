// CameraComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Mat4.h>
#include "../../Component.h"

namespace willow
{
	class ENGINE_API CameraComponent : public Component
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Component)

		/////////////////
		///   Types   ///
	public:

		enum class SplitScreenOrientation : int32
		{
			Top = 0,
			Bottom = 1
		};

		//////////////////
		///   Fields   ///
	public:

		/** The horizontal field of view of this Camera. */
		Angle fov = degrees(90.f);
		
		/** The distance to the near clipping plane. */
		float z_min = 0.1f;

		/** The distance to the far clipping plane. */
		float z_max = 100.f;

		SplitScreenOrientation orientation = SplitScreenOrientation::Bottom;

		///////////////////
		///   Methods   ///
	public:

		/** Generate a perspective projection matrix for this CameraComponent */
		FORCEINLINE Mat4 get_perspective_matrix(float screenRatio) const
		{
			return Mat4::PerspectiveHFOV(this->fov, screenRatio, this->z_min, this->z_max);
		}
	};
}
