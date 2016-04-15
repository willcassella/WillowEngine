// Physics.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <btBulletDynamicsCommon.h>
#include <Core/Math/Quat.h>
#include <Engine/Transform.h>

static_assert(std::is_same<Scalar, btScalar>::value, "The engine is not configured to use the same Scalar type as Bullet.");

namespace willow
{
	/////////////////////
	///   Functions   ///

	/** Converts a WillowEngine Vec3 to a Bullet btVector3. */
	inline btVector3 convert_to_bullet(const Vec3& vec)
	{
		return{ vec.X, vec.Y, vec.Z };
	}

	/** Converts a WillowEngine quaternion to a Bullet btQuaternion. */
	inline btQuaternion convert_to_bullet(const Quat& quat)
	{
		return{ -quat.X, -quat.Y, -quat.Z, quat.W };
	}

	/** Converts the given Transform to a Bullet btTransform (does not include scale). */
	inline btTransform convert_to_bullet(const Transform& transform)
	{
		return btTransform{ convert_to_bullet(transform.rotation), convert_to_bullet(transform.location) };
	}

	/** Converts a Bullet btVector3 to a WillowEngine Vec3. */
	inline Vec3 convert_from_bullet(const btVector3& vec)
	{
		return{ vec.x(), vec.y(), vec.z() };
	}

	/** Converts a Bullet btQuaternion to a WillowEngine Quat. */
	inline Quat convert_from_bullet(const btQuaternion& quat)
	{
		auto inverse = quat.inverse();
		return{ inverse.x(), inverse.y(), inverse.z(), inverse.w() };
	}
}
