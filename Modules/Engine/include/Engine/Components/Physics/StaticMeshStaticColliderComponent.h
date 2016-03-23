// StaticMeshStaticColliderComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Resource/AssetPtr.h>
#include "../../Assets/StaticMesh.h"
#include "ColliderComponent.h"

namespace Willow
{
	class ENGINE_API StaticMeshStaticColliderComponent final : public ColliderComponent
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(ColliderComponent)

		////////////////////////
		///   Constructors   ///
	public:
		
		StaticMeshStaticColliderComponent();
		~StaticMeshStaticColliderComponent() override;
		
		///////////////////
		///   Methods   ///
	public:

		void ToArchive(ArchiveWriter& writer) const override;

		void FromArchive(const ArchiveReader& reader) override;

		/** Returns the mesh currently used a collider. */
		AssetPtr<StaticMesh> GetMesh() const;

		/** Sets the mesh currently being used as a collider. */
		void SetMesh(AssetPtr<StaticMesh> mesh, UpdateEntityColliderOptions updateOptions = UpdateAll);

	private:

		btCollisionShape* GetCollisionShape() const override;

		void EDITOR_SetMesh(AssetPtr<StaticMesh> mesh);

		////////////////
		///   Data   ///
	public:

		std::unique_ptr<BulletTriangleMesh> _mesh;
		std::unique_ptr<btBvhTriangleMeshShape> _shape;
	};
}
