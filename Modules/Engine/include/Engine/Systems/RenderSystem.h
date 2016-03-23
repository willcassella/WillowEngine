// RenderSystem.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../System.h"

namespace Willow
{
	class ENGINE_API RenderSystem : public System
	{
		////////////////////////
		///   Constructors   ///
	public:

		using System::System;

		///////////////////
		///   Methods   ///
	public:

		virtual void RenderWorld(const World& world) = 0;
	};
}
