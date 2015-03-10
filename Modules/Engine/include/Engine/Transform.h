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

	Transform(Mobility mobility = Mobility::Static)
		: _mobility(mobility)
	{
		// All done
	}

	//////////////////
	///   Fields   ///
public:

	Vec3 Location = Vec3(0, 0, 0);
	Quat Orientation = Quat();
	Vec3 Scale3D = Vec3(1, 1, 1);
	Transform* Parent = nullptr;

	///////////////////
	///   Methods   ///
public:

	/** Formats the state of this Transform as a String */
	String ToString() const;

	/** Returns the mobility of this transform */
	FORCEINLINE Mobility GetMobility() const
	{
		return _mobility;
	}

	/** Returns whether this transform's mobility is "Static" */
	FORCEINLINE bool IsStatic() const
	{
		return _mobility == Mobility::Static;
	}

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

	// @TODO: Make this actually do something
	Mobility _mobility;
};