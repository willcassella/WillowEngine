// TriangleMesh.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <BulletCollision/CollisionShapes/btTriangleMesh.h>
#include <Resource/ResourceHandle.h>
#include <Engine/Resources/StaticMesh.h>

namespace willow
{
	struct TriangleMesh final : btTriangleMesh
	{
		/////////////////////////
		///   Constructors   ///
	public:

		TriangleMesh(ResourceHandle<StaticMesh> mesh);
	};
}
