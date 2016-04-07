// StaticMeshColliderComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Resource/AssetPtr.h>
#include "../../Assets/StaticMesh.h"
#include "ColliderComponent.h"

namespace Willow
{
	class ENGINE_API StaticMeshColliderComponent final : public ColliderComponent
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(ColliderComponent)

		/////////////////
		///   Types   ///
	public:

		struct Shape final
		{
			AssetPtr<StaticMesh> Mesh;
		};

		////////////////////////
		///   Constructors   ///
	public:
		
		StaticMeshColliderComponent();
		~StaticMeshColliderComponent() override;
		
		///////////////////
		///   Methods   ///
	public:

		void ToArchive(ArchiveWriter& writer) const override;

		void FromArchive(const ArchiveReader& reader) override;

		/** Returns the mesh currently used a collider. */
		FORCEINLINE AssetPtr<StaticMesh> GetMesh() const
		{
			return _shape.Mesh;
		}

		/** Sets the mesh currently being used as a collider. */
		void SetMesh(AssetPtr<StaticMesh> mesh);

		/** Returns the shape of this collider. */
		FORCEINLINE Shape GetShape() const
		{
			return _shape;
		}

		/** Sets the shape of this collider. */
		void SetShape(Shape shape);

	protected:

		void OnUpdateColliderTransform() override;

		bool OnActivate() override;

		void OnDeactivate() override;

	private:

		void UpdateShape();

		////////////////
		///   Data   ///
	public:

		Shape _shape;
	};
}
