// AnimationSystem.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../System.h"

namespace willow
{
	class ENGINE_API AnimationSystem final : public System
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(System)

		///////////////////
		///   Methods   ///
	public:

		void update(World& world) override;
	};
}
