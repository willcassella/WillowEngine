// Transform.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Umbrellas/Reflection.h>
#include <Core/Math/Mat4.h>
#include "config.h"

namespace Willow
{
	struct ENGINE_API Transform final : SerializeableStruct<Transform>
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_STRUCT

		//////////////////
		///   Fields   ///
	public:

		Vec3 Location;
		Quat Rotation;
		Vec3 Scale = { 1, 1, 1 };

		///////////////////
		///   Methods   ///
	public:

		/** Returns the transformation matrix for this Transform. */
		Mat4 GetMatrix() const;
	};
}
