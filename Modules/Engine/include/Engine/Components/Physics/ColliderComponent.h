// ColliderComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../../Component.h"

namespace willow
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
		FORCEINLINE bool is_activate() const
		{
			return this->_is_active;
		}

		/** Activates this ColliderComponent. */
		void activate_collider();

		/** Deactivates this ColliderComponent. */
		void deactivate_collider();

		/** Returns the local transform of this Collider. */
		FORCEINLINE const Transform& get_collider_transform() const
		{
			return this->_collider_transform;
		}

		/** Set the local transform of this Collider. */
		void set_collider_transform(const Transform& transform);

		/** Returns the local location of this Collider. */
		FORCEINLINE const Vec3& get_collider_location() const
		{
			return this->_collider_transform.location;
		}

		/** Sets the local location of this Collider. 
		* NOTE: If you're going to set more than one component of the local transform,
		* consider using 'set_collider_transform'. */
		void set_collider_location(const Vec3& location);

		/** Returns the local rotation of this Collider. */
		FORCEINLINE const Quat& get_collider_rotation() const
		{
			return this->_collider_transform.rotation;
		}

		/** Sets the local rotation of this Collider. 
		* NOTE: If you're going to set more than one component of the local transform,
		* consider using 'set_collider_transform'. */
		void set_collider_rotation(const Quat& rotation);

		/** Returns the local scale of this Collider. */
		FORCEINLINE const Vec3& get_collider_scale() const
		{
			return this->_collider_transform.scale;
		}

		/** Sets the local scale of this Collider. 
		* NOTE: If you're going to set more than one component of the local transform,
		* consider using 'set_collider_transform'. */
		void set_collider_scale(const Vec3& scale);

	protected:

		void on_initialize() final override;

		void on_destroy() final override;

		virtual void on_update_collider_transform() = 0;

		virtual bool on_activate() = 0;

		virtual void on_deactivate() = 0;

	private:

		void update_collider_transform();

		void EDITOR_set_active(bool active);

		////////////////
		///   Data   ///
	public:

		bool _is_active;
		Transform _collider_transform;
	};
}

REFLECTABLE_ENUM(ENGINE_API, willow::ColliderComponent::ShapeAxis)
