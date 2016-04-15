// SphereColliderComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "PrimitiveColliderComponent.h"

namespace willow
{
	class ENGINE_API SphereColliderComponent final : public PrimitiveColliderComponent
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(PrimitiveColliderComponent)

		/////////////////
		///   Types   ///
	public:

		/** Information about a sphere collider's shape. */
		struct Shape final
		{
			/** The radius of this Sphere. */
			float radius = 1.f;
		};

		////////////////////////
		///   Constructors   ///
	public:
		
		SphereColliderComponent();
		~SphereColliderComponent() override;

		///////////////////
		///   Methods   ///
	public:

		void ToArchive(ArchiveWriter& writer) const override;

		void FromArchive(const ArchiveReader& reader) override;

		FORCEINLINE float get_radius() const
		{
			return this->_shape.radius;
		}

		void set_radius(float radius);

		FORCEINLINE Shape get_shape() const
		{
			return this->_shape;
		}

		void set_shape(Shape shape);

	protected:

		void on_update_collider_transform() override;

		bool on_activate() override;

		void on_deactivate() override;

	private:

		void update_shape();

		////////////////
		///   Data   ///
	private:

		Shape _shape;
	};
}
