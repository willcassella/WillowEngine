// DebugDrawer.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../private/DebugDrawer.h"

namespace willow
{
	////////////////////////
	///   Constructors   ///

	DebugDrawer::DebugDrawer(RenderSystem& render)
		: _render{ &render }
	{
		// All done
	}

	///////////////////
	///   Methods   ///

	void DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	{
		RenderSystem::DebugLine line;
		line.start = convert_from_bullet(from);
		line.end = convert_from_bullet(to);
		line.color = convert_from_bullet(color);
		this->_render->draw_debug_line(line);
	}

	void DebugDrawer::drawContactPoint(const btVector3& /*pointOnB*/, const btVector3& /*normalOnB*/, btScalar /*distance*/, int /*lifeTime*/, const btVector3& /*color*/)
	{
		// Do nothing
	}

	void DebugDrawer::reportErrorWarning(const char* warningString)
	{
		Console::Warning("Bullet: @", warningString);
	}

	void DebugDrawer::draw3dText(const btVector3& /*location*/, const char* /*textString*/)
	{
		// Do nothing
	}

	void DebugDrawer::setDebugMode(int /*debugMode*/)
	{
		// Do nothing
	}

	int	DebugDrawer::getDebugMode() const
	{
		return DBG_DrawWireframe | DBG_DrawAabb;
	}
}
