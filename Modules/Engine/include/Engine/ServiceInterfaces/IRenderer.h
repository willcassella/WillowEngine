// IRenderer.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Forwards/Engine.h"
#include "../config.h"

/////////////////
///   Types   ///

namespace Willow
{
	class ENGINE_API IRenderer
	{
		////////////////////////
		///   Constructors   ///
	public:

		virtual ~IRenderer() = default;

		///////////////////
		///   Methods   ///
	public:

		virtual void RenderWorld(const World& world) = 0;
	};
}
