// StaticMesh.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <cmath>
#include <Core/IO/Console.h>
#include <Resource/Resources/BinaryData.h>
#include "../../include/Engine/Resources/StaticMesh.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::StaticMesh);

namespace willow
{
	////////////////////////
	///   Constructors   ///

	StaticMesh::StaticMesh(const Path& path)
	{
		const BinaryData file{ path };
		auto* cursor = file.get_data();

		// Get the number of vertices
		const auto numVerts = *reinterpret_cast<const uint32*>(cursor);

		cursor += sizeof(uint32);

		// Load in vertices
		this->vertices = Array<Vertex>(reinterpret_cast<const Vertex*>(cursor), numVerts);
	}

	///////////////////
	///   Methods   ///

	Vec3 StaticMesh::get_bounding_box() const
	{
		Vec3 result;

		for (const auto& vec : this->vertices)
		{
			result.X = std::max(std::abs(vec.position.X), std::abs(result.X));
			result.Y = std::max(std::abs(vec.position.Y), std::abs(result.Y));
		}

		return result;
	}
}
