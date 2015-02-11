// Quat.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Vec3.h"

// @TODO: conversion to Euler angles, conversion to axis+angle, and rotation by Euler angles

struct MATH_API Quat
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;

	////////////////////////
	///   Constructors   ///

	Quat();

	/** Constructs a new Quaternion
	* 'axis' - The axis about which this rotation represents
	* 'angle' - The amount (in degrees) to rotate about 'axis' */
	Quat(const Vec3& axis, float angle);

	//////////////////
	///   Fields   ///
public:

	float X, Y, Z, W;

	///////////////////
	///   Methods   ///
public:

	/** Formats this Quat as a String */
	String ToString() const;

	/** Rotate this quaternion around an axis by a certain angle */
	void RotateByAxisAngle(const Vec3& axis, float angle, bool local);

	/** Parse a Quat from a String */
	static String FromString(Quat& value, const String& string);

	/////////////////////
	///   Operators   ///

	friend MATH_API Quat operator*(const Quat& lhs, const Quat& rhs);
	friend MATH_API Quat& operator*=(Quat& lhs, const Quat& rhs);
	friend MATH_API inline bool operator==(const Quat& lhs, const Quat& rhs)
	{
		return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z;
	}
	friend MATH_API inline bool operator!=(const Quat& lhs, const Quat& rhs)
	{
		return lhs.X != rhs.X || lhs.Y != rhs.Y || lhs.Z != rhs.Z;
	}
};