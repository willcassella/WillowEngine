// BulletTriangleMesh.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <BulletCollision/CollisionShapes/btTriangleMesh.h>
#include <Resource/AssetPtr.h>
#include <Engine/Assets/StaticMesh.h>
#include "Common.h"

namespace Willow
{
	class BulletTriangleMesh final : public btTriangleMesh
	{
		/////////////////////////
		///   Constructors   ///
	public:

		BulletTriangleMesh(AssetPtr<StaticMesh> mesh)
			: _mesh(std::move(mesh))
		{
			this->btTriangleMesh::preallocateVertices(static_cast<int>(_mesh->Vertices.Size()));

			for (std::size_t i = 0; i < _mesh->Vertices.Size(); i += 3)
			{
				this->addTriangle(
					ConvertToBullet(_mesh->Vertices[i].Position),
					ConvertToBullet(_mesh->Vertices[i + 1].Position),
					ConvertToBullet(_mesh->Vertices[i + 2].Position));
			}
		}

		///////////////////
		///   Methods   ///
	public:

		AssetPtr<StaticMesh> GetMesh() const
		{
			return _mesh;
		}

		////////////////
		///   Data   ///
	private:

		AssetPtr<StaticMesh> _mesh;
	};
}
