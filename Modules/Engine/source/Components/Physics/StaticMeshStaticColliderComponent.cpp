// StaticMeshStaticColliderComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <BulletCollision/Gimpact/btGImpactShape.h>
#include "../../../include/Engine/Components/Physics/StaticMeshStaticColliderComponent.h"
#include "../../Physics/BulletTriangleMesh.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::StaticMeshStaticColliderComponent)
.Property("Mesh", &StaticMeshStaticColliderComponent::GetMesh, &StaticMeshStaticColliderComponent::EDITOR_SetMesh);

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	StaticMeshStaticColliderComponent::StaticMeshStaticColliderComponent()
	{
		// All done
	}

	StaticMeshStaticColliderComponent::~StaticMeshStaticColliderComponent()
	{
		// All done
	}

	///////////////////
	///   Methods   ///

	void StaticMeshStaticColliderComponent::ToArchive(ArchiveWriter& writer) const
	{
		Base::ToArchive(writer);
		writer.PushValue("Mesh", this->GetMesh());
	}

	void StaticMeshStaticColliderComponent::FromArchive(const ArchiveReader& reader)
	{
		Base::FromArchive(reader);
	
		auto mesh = this->GetMesh();
		reader.PullValue("Mesh", mesh);

		if (mesh != this->GetMesh())
		{
			this->SetMesh(mesh);
		}
	}

	AssetPtr<StaticMesh> StaticMeshStaticColliderComponent::GetMesh() const
	{
		return _mesh ? _mesh->GetMesh() : nullptr;
	}

	void StaticMeshStaticColliderComponent::SetMesh(AssetPtr<StaticMesh> mesh, UpdateEntityColliderOptions updateOptions)
	{
		auto isActive = this->IsActive();

		if (isActive)
		{
			this->DeactivateCollider(UpdateNothing);
		}

		_mesh = std::make_unique<BulletTriangleMesh>(mesh);
		_shape = std::make_unique<btBvhTriangleMeshShape>(_mesh.get(), true);
		
		if (isActive)
		{
			this->ActivateCollider(updateOptions);
		}
	}

	btCollisionShape* StaticMeshStaticColliderComponent::GetCollisionShape() const
	{
		return _shape.get();
	}

	void StaticMeshStaticColliderComponent::EDITOR_SetMesh(AssetPtr<StaticMesh> mesh)
	{
		this->SetMesh(mesh, UpdateAll);
	}
}
