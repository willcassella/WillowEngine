// DebugCamera.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Entity.h"

namespace Willow
{
	class ENGINE_API DebugCamera final : public Entity
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Entity)

		///////////////////
		///   Methods   ///
	protected:

		void OnInitialize() override;

		void OnSpawn() override;

	private:

		void Move(Vec2 dir);

		void Look(Vec2 dir);
	};
}
