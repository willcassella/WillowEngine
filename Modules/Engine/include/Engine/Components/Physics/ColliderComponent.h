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

		/** Some collider shapes may be aligned on different Axis (Capsules, Cones, Boxes, Cylinders). */
		enum class ShapeAxis : byte
		{
			/** This Collider is aligned along the X-axis. */
			X,

			/** This Collider is aligned along the Y-axis. */
			Y,

			/** This Collider is aligned along the Z-axis. */
			Z
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
		void ActivateCollider();

		/** Deactivates this ColliderComponent. */
		void DeactivateCollider();

		/** Returns the local transform of this Collider. */
		FORCEINLINE const Transform& GetColliderTransform() const
		{
			return _colliderTransform;
		}

		/** Set the local transform of this Collider. */
		void SetColliderTransform(const Transform& transform);

		/** Returns the local location of this Collider. */
		FORCEINLINE const Vec3& GetColliderLocation() const
		{
			return _colliderTransform.Location;
		}

		/** Sets the local location of this Collider. 
		* NOTE: If you're going to set more than one component of the local transform,
		* consider using 'SetColliderTransform'. */
		void SetColliderLocation(const Vec3& location);

		/** Returns the local rotation of this Collider. */
		FORCEINLINE const Quat& GetColliderRotation() const
		{
			return _colliderTransform.Rotation;
		}

		/** Sets the local rotation of this Collider. 
		* NOTE: If you're going to set more than one component of the local transform,
		* consider using 'SetColliderTransform'. */
		void SetColliderRotation(const Quat& rotation);

		/** Returns the local scale of this Collider. */
		FORCEINLINE const Vec3& GetColliderScale() const
		{
			return _colliderTransform.Scale;
		}

		/** Sets the local scale of this Collider. 
		* NOTE: If you're going to set more than one component of the local transform,
		* consider using 'SetColliderTransform'. */
		void SetColliderScale(const Vec3& scale);

	protected:

		void OnInitialize() final override;

		void OnSpawn() final override;

		void OnDestroy() final override;

		virtual void OnUpdateColliderTransform() = 0;

		virtual bool OnActivate() = 0;

		virtual void OnDeactivate() = 0;

	private:

		void UpdateColliderTransform();

		void EDITOR_SetActive(bool enabled);

		////////////////
		///   Data   ///
	public:

		bool _isActive;
		Transform _colliderTransform;
	};
}

REFLECTABLE_ENUM(ENGINE_API, Willow::ColliderComponent::ShapeAxis)
