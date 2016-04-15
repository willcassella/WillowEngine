// EntityCollider.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Common.h"

namespace willow
{
	/** Class used to represent colliders on entire Entities. */
	class EntityCollider final : public btCompoundShape
	{
		////////////////////////
		///   Constructors   ///
	public:

		EntityCollider();

		///////////////////
		///   Methods   ///
	public:

		/** Adds the given collision shape as a child of this EntityCollider. */
		void add_child(btCollisionShape& child, const Vec3& location, const Quat& rotation);

		/** Removes the given collision shape as a child of this EntityCollider. */
		void remove_child(btCollisionShape& child);

		/** Updates the location and rotation of the given child of this EntityCollider. */
		void update_child_location_rotation(btCollisionShape& child, const Vec3& location, const Quat& rotation);
	};
}
