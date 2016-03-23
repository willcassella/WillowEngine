// LineStructureComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Vec4.h>
#include "../../Component.h"

namespace Willow
{
	class ENGINE_API LineStructureComponent final : public Component
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Component)

		/////////////////
		///   Types   ///
	public:

		struct Line final
		{
			/** The world location this Line originates from. */
			Vec3 Start;
			
			/** The world location this Line ends at. */
			Vec3 End;
			
			/** The color of this Line. */
			Vec3 Color;
		};

		//////////////////
		///   Fields   ///
	public:

		Array<Line> Lines;
	};
}
