// EntityCollider.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Physics.h"

namespace Willow
{
	/** Class used to represent colliders on entire Entities. */
	class EntityCollider final : public btCompoundShape
	{
		////////////////////////
		///   Constructors   ///
	public:

		EntityCollider()
			: btCompoundShape{ /*enableDynamicAabbTree*/ false }
		{
			// All done
		}

		///////////////////
		///   Methods   ///
	public:

		void AddChild(btCollisionShape& child, const Vec3& location, const Quat& rotation)
		{
			const btTransform transform{ ConvertToBullet(rotation), ConvertToBullet(location) };
			this->addChildShape(transform, &child);
		}

		void RemoveChild(btCollisionShape& child)
		{
			this->removeChildShape(&child);
		}

		void UpdateChildLocationRotation(btCollisionShape& child, const Vec3& location, const Quat& rotation)
		{
			const auto childList = this->getChildList();
			const auto numChildren = this->getNumChildShapes();

			for (int i = 0; i < numChildren; ++i)
			{
				if (childList[i].m_childShape == &child)
				{
					const btTransform transform{ ConvertToBullet(rotation), ConvertToBullet(location) };
					this->updateChildTransform(i, transform, /*shouldRecalculateLocalAabb*/ false);
					return;
				}
			}
		}
	};
}
