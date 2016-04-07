// Physics.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <btBulletDynamicsCommon.h>
#include <Core/Math/Quat.h>

static_assert(std::is_same<Scalar, btScalar>::value, "The engine is not configured to use the same Scalar type as Bullet.");

namespace Willow
{
	/////////////////////
	///   Functions   ///

	/** Converts a WillowEngine Vec3 to a Bullet btVector3. */
	inline btVector3 ConvertToBullet(const Vec3& vec)
	{
		return{ vec.X, vec.Y, vec.Z };
	}

	/** Converts a WillowEngine quaternion to a Bullet btQuaternion. */
	inline btQuaternion ConvertToBullet(const Quat& quat)
	{
		return{ -quat.X, -quat.Y, -quat.Z, quat.W };
	}

	/** Converts a Bullet btVector3 to a WillowEngine Vec3. */
	inline Vec3 ConvertFromBullet(const btVector3& vec)
	{
		return{ vec.x(), vec.y(), vec.z() };
	}

	/** Converts a Bullet btQuaternion to a WillowEngine Quat. */
	inline Quat ConvertFromBullet(const btQuaternion& quat)
	{
		auto inverse = quat.inverse();
		return{ inverse.x(), inverse.y(), inverse.z(), inverse.w() };
	}
}
