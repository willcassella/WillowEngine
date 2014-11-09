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

		float X, Y, Z; // Position coordinates
		float U, V; // UV coordinates
		float I, J, K; // Normal direction

		/////////////////////
		///   Operators   ///
	public:

		friend RENDER_API bool operator==(const Vertex& lhs, const Vertex& rhs);
		friend RENDER_API inline bool operator!=(const Vertex& lhs, const Vertex& rhs)
		{
			return !(lhs == rhs);
		}
	};

	NON_REFLECTABLE(Willow::Vertex)
}