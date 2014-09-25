// Vertex.h
#pragma once

#include <Utility\Math\Vec2.h>
#include <Utility\Math\Vec3.h>
#include "config.h"

namespace Willow
{
	struct RENDER_API Vertex
	{
		//////////////////
		///   Fields   ///
	public:

		Vec3 Position;
		Vec2 TextureCoordinates;
		Vec3 Normal;

		/////////////////////
		///   Operators   ///
	public:

		friend bool RENDER_API operator==(const Vertex& lhs, const Vertex& rhs);
		friend bool RENDER_API operator!=(const Vertex& lhs, const Vertex& rhs);
	};
}