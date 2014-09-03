// Vertex.h
#pragma once

#include <Utility\Math\Vec2.h>
#include <Utility\Math\Vec3.h>
#include "config.h"

namespace Render
{
	struct RENDER_API Vertex
	{
		//////////////////
		///   Fields   ///
	public:

		Math::Vec3 position;
		Math::Vec2 coordinates;
		Math::Vec3 normal;

		/////////////////////
		///   Operators   ///
	public:

		bool operator==(const Vertex& rhs);
		bool operator!=(const Vertex& rhs);
	};
}