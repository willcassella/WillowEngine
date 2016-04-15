// TriangleMesh.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Resource/ResourceManager.h>
#include "../private/TriangleMesh.h"
#include "../private/Common.h"

namespace willow
{
	/////////////////////////
	///   Constructors   ///

	TriangleMesh::TriangleMesh(ResourceHandle<StaticMesh> mesh)
	{
		const auto* meshResource = ResourceManager::get_resource(mesh);
		this->btTriangleMesh::preallocateVertices(static_cast<int>(meshResource->vertices.Size()));

		for (std::size_t i = 0; i < meshResource->vertices.Size(); i += 3)
		{
			this->addTriangle(
				convert_to_bullet(meshResource->vertices[i].position),
				convert_to_bullet(meshResource->vertices[i + 1].position),
				convert_to_bullet(meshResource->vertices[i + 2].position));
		}
	}
}
