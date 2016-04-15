// CapsuleColliderComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "PrimitiveColliderComponent.h"

namespace willow
{
	class ENGINE_API CapsuleColliderComponent final : public PrimitiveColliderComponent
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(PrimitiveColliderComponent)

		/////////////////
		///   Types   ///
	public:

		/** Information about a capsule collider's shape. */
		struct Shape final
		{
			/** The radius of the Capsule. */
			float radius = 1.f;

			/** The height of the Capsule. */
			float height = 3.f;

			/** The axis of the Capsule. */
			ShapeAxis axis = ShapeAxis::Y;
		};

		////////////////////////
		///   Constructors   ///
	public:

		CapsuleColliderComponent();
		~CapsuleColliderComponent() override;

		///////////////////
		///   Methods   ///
	public:
		
		void ToArchive(ArchiveWriter& writer) const override;

		void FromArchive(const ArchiveReader& reader) override;

		/** Returns the radius of this CapsuleComponent. */
		FORCEINLINE float get_radius() const
		{
			return _shape.radius;
		}

		/** Sets the radius of this CapsuleComponent.
		* NOTE: If you're going to set the radius, height, and axis, prefer to use 'set_shape'. */
		void set_radius(float radius);

		/** Returns the height of this capsule. */
		FORCEINLINE float get_height() const
		{
			return this->_shape.height;
		}

		/** Sets the height of this CapsuleComponent.
		* NOTE: If you're going to set the radius, height, and axis, prefer to use 'set_shape'. */
		void set_height(float height);

		/** Returns the axis that this CapsuleComponent is aligned along. */
		FORCEINLINE ShapeAxis get_axis() const
		{
			return this->_shape.axis;
		}

		/** Sets the axis that this CapsuleComponent is aligned along. */
		void set_axis(ShapeAxis axis);

		/** Returns the whole shape of this Collider. */
		FORCEINLINE Shape get_shape() const
		{
			return this->_shape;
		}

		/** Sets the whole shape of this Collider. */
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
