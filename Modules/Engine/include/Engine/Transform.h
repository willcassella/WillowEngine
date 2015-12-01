// Transform.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Mat4.h>
#include <Core/Object.h>
#include "config.h"

class ENGINE_API Transform final : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Object)

	///////////////////////
	///   Inner Types   ///
public:

	/** Possible different modes of mobility */
	enum class Mobility : byte
	{
		Static,
		Dynamic
	};

	//////////////////
	///   Fields   ///
public:

	Vec3 Location = Vec3(0, 0, 0);
	Quat Orientation = Quat();
	Vec3 Scale = Vec3(1, 1, 1);

	///////////////////
	///   Methods   ///
public:

	/** Returns the mobility state of this Transform. */
	FORCEINLINE Mobility GetMobility() const
	{
		return _mobility;
	}

	/** Formats the state of this Transform as a String. */
	String ToString() const override;

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

	/** Returns the parent of this Transform. */
	Transform* GetParent()
	{
		return _parent.Get();
	}

	/** Returns the parent of this Transform. */
	const Transform* GetParent() const
	{
		return _parent.Get();
	}

	/** Sets the parent of this Transform. */
	void SetParent(Transform* parent)
	{
		_parent = parent;
	}

	////////////////
	///   Data   ///
private:

	Mobility _mobility = Mobility::Dynamic;
	Ptr<Transform> _parent;
};
REFLECTABLE_ENUM(Transform::Mobility);
