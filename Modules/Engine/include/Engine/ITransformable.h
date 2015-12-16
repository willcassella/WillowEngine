// ITransformable.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Quat.h>
#include "config.h"

class ENGINE_API ITransformable
{
	////////////////////////
	///   Constructors   ///
public:

	virtual ~ITransformable() = default;

	///////////////////
	///   Methods   ///
public:

	/** Sets the location of this object relative to its parent. 
	* NOTE: If this object has no parent, this has the same effect as "SetWorldLocation". */
	virtual void SetLocation(const Vec3& vec) = 0;

	/** Sets the location of this object in world space. */
	virtual void SetWorldLocation(const Vec3& vec) = 0;

	/** Translates this object along the given vector, in local space. */
	virtual void Translate(const Vec3& vec) = 0;

	/** Translates this object along the given vector, in world space. */
	virtual void TranslateGlobal(const Vec3& vec) = 0;

	/** Sets the rotation of this object relative to its parent.
	* NOTE: If this object has no parent, this has the same effect as "SetWorldRotation". */
	virtual void SetRotation(const Quat& rot) = 0;

	/** Sets the rotation of this object in world space. */
	virtual void SetWorldRotation(const Quat& rot) = 0;

	/** Rotates this object along the given axis by the given angle, in local space. */
	virtual void Rotate(const Vec3& axis, Angle angle) = 0;

	/** Rotates this object along the given axis by the given angle, in world space. */
	virtual void RotateGlobal(const Vec3& axis, Angle angle) = 0;

	/** Sets the scale of this object to the given value. */
	virtual void SetScale(const Vec3& scale) = 0;

	/** Scales this object by the given value. */
	virtual void Scale(const Vec3& scale) = 0;
};
