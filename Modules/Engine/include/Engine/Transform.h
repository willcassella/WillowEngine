// Transform.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Umbrellas/Reflection.h>
#include <Core/Math/Mat4.h>
#include "config.h"

namespace willow
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

		Vec3 location;
		Quat rotation;
		Vec3 scale = { 1, 1, 1 };

		///////////////////
		///   Methods   ///
	public:

		/** Returns the transformation matrix for this Transform. */
		Mat4 get_matrix() const;
	};
}
