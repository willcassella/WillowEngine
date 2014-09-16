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

		bool operator==(const Vertex& rhs);
		bool operator!=(const Vertex& rhs);
	};
}