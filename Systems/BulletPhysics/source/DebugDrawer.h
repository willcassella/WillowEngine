// DebugDrawer.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/IO/Console.h>
#include <Engine/Systems/RenderSystem.h>
#include "Common.h"

namespace Willow
{
	class DebugDrawer final : public btIDebugDraw
	{
		////////////////////////
		///   Constructors   ///
	public:

		DebugDrawer(RenderSystem& render)
			: _render{ &render }
		{
			// All done
		}

		///////////////////
		///   Methods   ///
	private:

		void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override
		{
			RenderSystem::DebugLine line;
			line.Start = Willow::ConvertFromBullet(from);
			line.End = Willow::ConvertFromBullet(to);
			line.Color = Willow::ConvertFromBullet(color);
			_render->DrawDebugLine(line);
		}

		void drawContactPoint(const btVector3& /*PointOnB*/, const btVector3& /*normalOnB*/, btScalar /*distance*/, int /*lifeTime*/, const btVector3& /*color*/) override
		{
			// Do nothing
		}

		void reportErrorWarning(const char* warningString) override
		{
			Console::Warning("Bullet: @", warningString);
		}

		void draw3dText(const btVector3& /*location*/, const char* /*textString*/) override
		{
			// Do nothing
		}

		void setDebugMode(int /*debugMode*/) override
		{
			// Do nothing
		}

		int	getDebugMode() const override
		{
			return DBG_DrawWireframe | DBG_DrawAabb;
		}

		////////////////
		///   Data   ///
	private:

		RenderSystem* _render;
	};
}
