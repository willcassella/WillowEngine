// CapsuleColliderComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "ColliderComponent.h"

namespace Willow
{
	class ENGINE_API CapsuleColliderComponent final : public ColliderComponent
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(ColliderComponent)

		/////////////////
		///   Types   ///
	public:

		/** Information about a capsule collider's shape. */
		struct Shape final
		{
			/** The radius of the Capsule. */
			float Radius = 1.f;

			/** The height of the Capsule. */
			float Height = 3.f;

			/** The axis of the Capsule. */
			ShapeAxis Axis = ShapeAxis::Y;
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
		FORCEINLINE float GetRadius() const
		{
			return _shape.Radius;
		}

		/** Sets the radius of this CapsuleComponent.
		* NOTE: If you're going to set the radius, height, and axis, prefer to use 'SetShape'. */
		void SetRadius(float radius);

		/** Returns the height of this capsule. */
		FORCEINLINE float GetHeight() const
		{
			return _shape.Height;
		}

		/** Sets the height of this CapsuleComponent.
		* NOTE: If you're going to set the radius, height, and axis, prefer to use 'SetShape'. */
		void SetHeight(float height);

		/** Returns the axis that this CapsuleComponent is aligned along. */
		FORCEINLINE ShapeAxis GetAxis() const
		{
			return _shape.Axis;
		}

		/** Sets the axis that this CapsuleComponent is aligned along. */
		void SetAxis(ShapeAxis axis);

		/** Returns the whole shape of this Collider. */
		FORCEINLINE Shape GetShape() const
		{
			return _shape;
		}

		/** Sets the whole shape of this Collider. */
		void SetShape(Shape shape);

	protected:

		void OnUpdateColliderTransform() override;

		bool OnActivate() override;

		void OnDeactivate() override;

	private:

		void UpdateShape();

		////////////////
		///   Data   ///
	private:

		Shape _shape;
	};
}
