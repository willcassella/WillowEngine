// Mesh.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <cmath>
#include <Core/IO/Console.h>
#include <Resource/Resources/BinaryFile.h>
#include "../../include/Engine/Assets/StaticMesh.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::StaticMesh);

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	StaticMesh::StaticMesh(const Path& path)
		: Base(path)
	{
		BinaryFile file(path);
		const byte* cursor = file.GetData();

		// Get the number of vertices
		uint32 numVerts = *reinterpret_cast<const uint32*>(cursor);

		cursor += sizeof(uint32);

		// Load in vertices
		Vertices = Array<Vertex>(reinterpret_cast<const Vertex*>(cursor), numVerts);
	}

	///////////////////
	///   Methods   ///

	Vec3 StaticMesh::GetBoundingBox() const
	{
		Vec3 result;

		for (const auto& vec : Vertices)
		{
			result.X = std::max(std::abs(vec.Position.X), std::abs(result.X));
			result.Y = std::max(std::abs(vec.Position.Y), std::abs(result.Y));
		}

		return result;
	}
}
