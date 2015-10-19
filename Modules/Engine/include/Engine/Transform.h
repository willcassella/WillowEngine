// Transform.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Mat4.h>
#include "config.h"

struct ENGINE_API Transform final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	//////////////////
	///   Fields   ///
public:

	Vec3 Location = Vec3(0, 0, 0);
	Quat Orientation = Quat();
	Vec3 Scale = Vec3(1, 1, 1);

	///////////////////
	///   Methods   ///
public:

	/** Formats the state of this Transform as a String. */
	String ToString() const;

	/** Translates this transform by the given vector.
	* 'vec' - The vector to translate this transform by.
	* 'isLocal' - Whether to translate in local space. */
	void Translate(const Vec3& vec, bool isLocal = true);

	/** Scales this transform by the given vector.
	* 'vec' - The vector to scale this transform by.
	* 'isLocal' - Whether to scale in local space. */
	void Scale3D(const Vec3& vec, bool isLocal = true);

	/** Rotates this transform by the given axis and angle.
	* 'axis' - The axis about which to rotate.
	* 'isLocal' - Whether to rotate in local space. */
	void Rotate(const Vec3& axis, float angle, bool isLocal = true);

	/** Returns the transformation matrix for this Transform. */
	Mat4 GetMatrix() const;
};