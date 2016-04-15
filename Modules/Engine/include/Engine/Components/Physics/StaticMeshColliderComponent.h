// StaticMeshColliderComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Resource/ResourceManager.h>
#include "../../Resources/StaticMesh.h"
#include "ColliderComponent.h"

namespace willow
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
			ResourceHandle<StaticMesh> mesh;
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
		FORCEINLINE ResourceHandle<StaticMesh> get_mesh() const
		{
			return this->_shape.mesh;
		}

		/** Sets the mesh currently being used as a collider. */
		void set_mesh(ResourceHandle<StaticMesh> mesh);

		/** Returns the shape of this collider. */
		FORCEINLINE Shape get_shape() const
		{
			return this->_shape;
		}

		/** Sets the shape of this collider. */
		void set_shape(Shape shape);

	protected:

		void on_update_collider_transform() override;

		bool on_activate() override;

		void on_deactivate() override;

	private:

		void update_shape();

		////////////////
		///   Data   ///
	public:

		Shape _shape;
	};
}
