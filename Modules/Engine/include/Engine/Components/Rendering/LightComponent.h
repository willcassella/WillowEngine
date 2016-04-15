// LightComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Vec3.h>
#include "../../Component.h"

namespace willow
{
	class ENGINE_API LightComponent : public Component
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Component)

		//////////////////
		///   Fields   ///
	public:

		/** The color of the light. */
		Vec3 color = Vec3{ 1.f, 1.f, 1.f };

		/** The intensity of this light. */
		float intensity = 1.f;
	};
}
