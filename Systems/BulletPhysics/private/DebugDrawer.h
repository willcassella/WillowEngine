// DebugDrawer.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Systems/RenderSystem.h>
#include "Common.h"

namespace willow
{
	class DebugDrawer final : public btIDebugDraw
	{
		////////////////////////
		///   Constructors   ///
	public:

		DebugDrawer(RenderSystem& render);

		///////////////////
		///   Methods   ///
	private:

		void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;

		void drawContactPoint(const btVector3& pointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override;

		void reportErrorWarning(const char* warningString) override;

		void draw3dText(const btVector3& location, const char* textString) override;

		void setDebugMode(int debugMode) override;

		int	getDebugMode() const override;

		////////////////
		///   Data   ///
	private:

		RenderSystem* _render;
	};
}
