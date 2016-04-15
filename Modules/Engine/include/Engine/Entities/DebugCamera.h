// DebugCamera.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Entity.h"

namespace willow
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

		void on_initialize() override;

		void on_spawn() override;

	private:

		void on_move(Vec2 dir);

		void on_look(Vec2 dir);
	};
}
