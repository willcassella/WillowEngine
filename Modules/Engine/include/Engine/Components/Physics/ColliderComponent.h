// ColliderComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../../Component.h"

namespace Willow
{
	class ENGINE_API ColliderComponent : public Component
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Component)

		/////////////////
		///   Types   ///
	public:

		/** Some collider types may be aligned on different Axis (Capsules, Cones, Boxes, Cylindars). */
		enum class Axis : int
		{
			/** This Collider is aligned along the X-axis. */
			X = 0,
			
			/** This Collider is aligned along the Y-axis. */
			Y = 1,
			
			/** This Collider is aligned along the Z-axis. */
			Z = 2
		};

		/** Options for handling changes to the owning Entity's collider.
		* For efficiency reasons, you should avoid updating inertia and AABB of an Entity until you're done with all modifications to its colliders. */
		enum UpdateEntityColliderOptions
		{
			/** Do nothing. */
			UpdateNothing = 0,

			/** Update the inertia of the owning Entity. */
			UpdateInertia = 1 << 0,

			/** Update the Entity's AABB. */
			UpdateAABB = 1 << 1,

			/** Update both the inertia and the AABB. */
			UpdateAll = UpdateInertia | UpdateAABB
		};

		////////////////////////
		///   Constructors   ///
	public:

		ColliderComponent();

		///////////////////
		///   Methods   ///
	public:

		/** Returns whether this ColliderComponent is currently active. */
		FORCEINLINE bool IsActive() const
		{
			return _isActive;
		}

		/** Activates this ColliderComponent. */
		void ActivateCollider(UpdateEntityColliderOptions updateOptions = UpdateAll);

		/** Deactivates this ColliderComponent. */
		void DeactivateCollider(UpdateEntityColliderOptions updateOptions = UpdateAll);

		/** Returns the local transform of this Collider. */
		FORCEINLINE const Transform& GetColliderTransform() const
		{
			return _colliderTransform;
		}

		/** Set the local transform of this Collider. */
		void SetColliderTransform(const Transform& transform, UpdateEntityColliderOptions updateOptions = UpdateAll);

		/** Returns the local location of this Collider. */
		FORCEINLINE const Vec3& GetColliderLocation() const
		{
			return _colliderTransform.GetLocation();
		}

		/** Sets the local location of this Collider. 
		* NOTE: If you're going to set more than one component of the local transform,
		* consider using 'SetColliderTransform'. */
		void SetColliderLocation(const Vec3& location, UpdateEntityColliderOptions updateOptions = UpdateAll);

		/** Returns the local rotation of this Collider. */
		FORCEINLINE const Quat& GetColliderRotation() const
		{
			return _colliderTransform.GetRotation();
		}

		/** Sets the local rotation of this Collider. 
		* NOTE: If you're going to set more than one component of the local transform,
		* consider using 'SetColliderTransform'. */
		void SetColliderRotation(const Quat& rotation, UpdateEntityColliderOptions updateOptions = UpdateAll);

		/** Returns the local scale of this Collider. */
		FORCEINLINE const Vec3& GetColliderScale() const
		{
			return _colliderTransform.GetScale();
		}

		/** Sets the local scale of this Collider. 
		* NOTE: If you're going to set more than one component of the local transform,
		* consider using 'SetColliderTransform'. */
		void SetColliderScale(const Vec3& scale, UpdateEntityColliderOptions updateOptions = UpdateAll);

		/** Updates the entity's collider.
		* NOTE: This should be called after any modifications to child colliders, if it has not been already. */
		void UpdateEntityCollider(UpdateEntityColliderOptions updateOptions = UpdateAll);

	protected:

		void OnSpawn() override;

		void OnDestroy() override;

	private:

		virtual btCollisionShape* GetCollisionShape() const = 0;

		void EDITOR_SetActive(bool enabled);

		void EDITOR_SetColliderLocation(const Vec3& location);

		void EDITOR_SetColliderRotation(const Quat& rotation);

		void EDITOR_SetColliderScale(const Vec3& scale);

		////////////////
		///   Data   ///
	public:

		bool _isActive;
		Transform _colliderTransform;
	};
}

REFLECTABLE_ENUM(ENGINE_API, Willow::ColliderComponent::Axis)
