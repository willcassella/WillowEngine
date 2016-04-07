// StaticMeshColliderComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Engine/Components/Physics/StaticMeshColliderComponent.h"
#include "../../../include/Engine/World.h"
#include "../../../include/Engine/Systems/PhysicsSystem.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::StaticMeshColliderComponent)
.Property("Mesh", &StaticMeshColliderComponent::GetMesh, &StaticMeshColliderComponent::SetMesh);

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	StaticMeshColliderComponent::StaticMeshColliderComponent()
	{
		// All done
	}

	StaticMeshColliderComponent::~StaticMeshColliderComponent()
	{
		// All done
	}

	///////////////////
	///   Methods   ///

	void StaticMeshColliderComponent::ToArchive(ArchiveWriter& writer) const
	{
		this->Base::ToArchive(writer);
		writer.PushValue("Mesh", _shape.Mesh);
	}

	void StaticMeshColliderComponent::FromArchive(const ArchiveReader& reader)
	{
		this->Base::FromArchive(reader);
		reader.PullValue("Mesh", _shape.Mesh);
		this->UpdateShape();
	}

	void StaticMeshColliderComponent::SetMesh(AssetPtr<StaticMesh> mesh)
	{
		_shape.Mesh = mesh;
		this->UpdateShape();
	}

	void StaticMeshColliderComponent::SetShape(Shape shape)
	{
		_shape = shape;
		this->UpdateShape();
	}

	void StaticMeshColliderComponent::OnUpdateColliderTransform()
	{
		this->GetWorld().GetSystem<PhysicsSystem>()->SetColliderTransform(*this, this->GetColliderTransform());
	}

	bool StaticMeshColliderComponent::OnActivate()
	{
		if (_shape.Mesh)
		{
			this->GetWorld().GetSystem<PhysicsSystem>()->CreateCollider(*this, this->GetEntity(), this->GetColliderTransform(), _shape);
			return true;
		}
		else
		{
			return false;
		}
	}

	void StaticMeshColliderComponent::OnDeactivate()
	{
		this->GetWorld().GetSystem<PhysicsSystem>()->DestroyCollider(*this);
	}

	void StaticMeshColliderComponent::UpdateShape()
	{
		this->GetWorld().GetSystem<PhysicsSystem>()->SetColliderShape(*this, _shape);
	}
}
