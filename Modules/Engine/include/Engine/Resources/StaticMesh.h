// StaticMesh.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Vec3.h>
#include <Resource/Path.h>
#include "../config.h"

namespace willow
{
	class ENGINE_API StaticMesh final
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_STRUCT

		/////////////////
		///   Types   ///
	public:

		struct Vertex final
		{
			//////////////////
			///   Fields   ///
		public:

			Vec3 position;	// Position coordinates
			Vec2 uv;		// UV coordinates
			Vec3 normal;	// Normal direction

			/////////////////////
			///   Operators   ///
		public:

			friend FORCEINLINE bool operator==(const Vertex& lhs, const Vertex& rhs)
			{
				return lhs.position == rhs.position && lhs.uv == rhs.uv && lhs.normal == rhs.normal;
			}
			friend FORCEINLINE bool operator!=(const Vertex& lhs, const Vertex& rhs)
			{
				return !(lhs == rhs);
			}
		};

		////////////////////////
		///   Constructors   ///
	public:

		StaticMesh(const Path& path);

		//////////////////
		///   Fields   ///
	public:

		Array<Vertex> vertices;

		///////////////////
		///   Methods   ///
	public:

		/** Returns the lengths of a bounding box containing this StaticMesh. */
		Vec3 get_bounding_box() const;
	};
}
