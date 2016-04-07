// SphereColliderComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "ColliderComponent.h"

namespace Willow
{
	class ENGINE_API SphereColliderComponent final : public ColliderComponent
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(ColliderComponent)

		/////////////////
		///   Types   ///
	public:

		/** Information about a sphere collider's shape. */
		struct Shape final
		{
			/** The radius of this Sphere. */
			float Radius = 1.f;
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

		FORCEINLINE float GetRadius() const
		{
			return _shape.Radius;
		}

		void SetRadius(float radius);

		FORCEINLINE Shape GetShape() const
		{
			return _shape;
		}

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
