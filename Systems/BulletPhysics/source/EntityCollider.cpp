// EntityCollider.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../private/EntityCollider.h"

namespace willow
{
	////////////////////////
	///   Constructors   ///

	EntityCollider::EntityCollider()
		: btCompoundShape{ /*enableDynamicAabbTree*/ false }
	{
		// All done
	}

	///////////////////
	///   Methods   ///

	void EntityCollider::add_child(btCollisionShape& child, const Vec3& location, const Quat& rotation)
	{
		const btTransform transform{ convert_to_bullet(rotation), convert_to_bullet(location) };
		child.setLocalScaling(this->getLocalScaling());
		this->addChildShape(transform, &child);
	}

	void EntityCollider::remove_child(btCollisionShape& child)
	{
		this->removeChildShape(&child);
	}

	void EntityCollider::update_child_location_rotation(btCollisionShape& child, const Vec3& location, const Quat& rotation)
	{
		const auto childList = this->getChildList();
		const auto numChildren = this->getNumChildShapes();

		for (int i = 0; i < numChildren; ++i)
		{
			if (childList[i].m_childShape == &child)
			{
				const btTransform transform{ convert_to_bullet(rotation), convert_to_bullet(location) };
				this->updateChildTransform(i, transform, /*shouldRecalculateLocalAabb*/ true);
				return;
			}
		}
	}
}
