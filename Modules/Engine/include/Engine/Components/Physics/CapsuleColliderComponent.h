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

		/////////////////////
		///   Constants   ///
	public:

		/** The default radius for CapsuleColliders. */
		static constexpr float DefaultRadius = 1.f;

		/** The default height for CapsuleColliders. */
		static constexpr float DefaultHeight = 3.f;

		/** The default Axis for CapsuleColliders. */
		static constexpr Axis DefaultAxis = Axis::Y;

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
		float GetRadius() const;

		/** Sets the radius of this CapsuleComponent.
		* NOTE: If you're going to set the radius, height, and axis, prefer to use 'Set'. */
		void SetRadius(float radius, UpdateEntityColliderOptions updateOptions = UpdateAll);

		/** Returns the height of this capsule. */
		float GetHeight() const;

		/** Sets the height of this CapsuleComponent.
		* NOTE: If you're going to set the radius, height, and axis, prefer to use 'Set'. */
		void SetHeight(float height, UpdateEntityColliderOptions updateOptions = UpdateAll);

		/** Returns the axis that this CapsuleComponent is aligned along. */
		Axis GetAxis() const;

		/** Sets the axis that this CapsuleComponent is aligned along. */
		void SetAxis(Axis axis, UpdateEntityColliderOptions updateOptions = UpdateAll);

		/** Sets the radius and height of this Capsule. */
		void Set(float radius, float height, Axis axis, UpdateEntityColliderOptions = UpdateAll);

	protected:

		void OnSpawn() override;

	private:

		btCollisionShape* GetCollisionShape() const override;

		void EDITOR_SetRadius(float radius);

		void EDITOR_SetHeight(float height);

		void EDITOR_SetAxis(Axis axis);

		////////////////
		///   Data   ///
	private:

		std::unique_ptr<btCapsuleShape> _shape;
	};
}
