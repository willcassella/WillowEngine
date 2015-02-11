// Transform.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Math/Mat4.h>
#include "config.h"

enum class Mobility
{
	Static, 
	Moveable
};

struct ENGINE_API Transform final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;

	////////////////////////
	///   Constructors   ///
public:

	Transform(Mobility mobility = Mobility::Static, const Vec3& location = Vec3(), const Quat& orientation = Quat(), const Vec3& scale3D = Vec3(1.f, 1.f, 1.f));

	//////////////////
	///   Fields   ///
public:

	Vec3 Location;
	Quat Orientation;
	Vec3 Scale3D;
	// @TODO: encapsulate this better
	Transform* Parent;

	///////////////////
	///   Methods   ///
public:

	/** Formats the state of this Transform as a String */
	String ToString() const;

	/** Returns the mobility of this transform */
	Mobility GetMobility() const;

	/** Returns whether this transform's mobility is "Static" */
	bool IsStatic() const;

	/** Translates this transform by the given vector
	* 'vec' - The vector to translate this transform by
	* 'isLocal' - Whether to translate in local space */
	void Translate(const Vec3& vec, bool isLocal = true);

	/** Scales this transform by the given vector
	* 'vec' - The vector to scale this transform by 
	* 'isLocal' - Whether to scale in local space */
	void Scale(const Vec3& vec, bool isLocal = true);

	/** Rotates this transform by the given axis and angle
	* 'axis' - The axis about which to rotate 
	* 'isLocal' - Whether to rotate in local space */
	void Rotate(const Vec3& axis, float angle, bool isLocal = true);

	/** Returns the transformation matrix represented by this transform */
	Mat4 GetTransfomationMatrix() const;

	////////////////
	///   Data   ///
private:

	Mobility _mobility;
};