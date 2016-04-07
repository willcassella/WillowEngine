// RenderSystem.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Vec3.h>
#include "../System.h"

namespace Willow
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
			Vec3 Start;

			/** The world location this Line ends at. */
			Vec3 End;

			/** The color of this Line. */
			Vec3 Color;
		};

		///////////////////
		///   Methods   ///
	public:

		virtual void RenderWorld(const World& world) = 0;

		virtual void DrawDebugLine(const DebugLine& line) = 0;
	};
}
