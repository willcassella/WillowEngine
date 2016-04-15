// RenderSystem.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Vec3.h>
#include "../System.h"

namespace willow
{
	class ENGINE_API RenderSystem : public System
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(System)

		/////////////////
		///   Types   ///
	public:

		struct DebugLine final
		{
			/** The world location this Line originates from. */
			Vec3 start;

			/** The world location this Line ends at. */
			Vec3 end;

			/** The color of this Line. */
			Vec3 color;
		};

		///////////////////
		///   Methods   ///
	public:

		virtual void render_world(const World& world) = 0;

		virtual void draw_debug_line(const DebugLine& line) = 0;
	};
}
