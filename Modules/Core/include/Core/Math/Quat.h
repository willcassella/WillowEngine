// Quat.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Vec3.h"

// @TODO: conversion to Euler angles, conversion to axis+angle, and rotation by Euler angles
struct CORE_API Quat final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	////////////////////////
	///   Constructors   ///
public:

	constexpr Quat()
		: X(0), Y(0), Z(0), W(1)
	{
		// All done
	}

	/** Constructs a new Quaternion
	* 'axis' - The axis about which this rotation represents
	* 'angle' - The amount (in degrees) to rotate about 'axis' */
	Quat(const Vec3& axis, float angle)
	{
		// Make sure the axis vector is normalized
		Vec3 normAxis = axis.Normalize();
		float sinHalfAngle = sinf(angle * 0.5f);

		W = cosf(angle / 2);
		X = normAxis.X * sinHalfAngle;
		Y = normAxis.Y * sinHalfAngle;
		Z = normAxis.Z * sinHalfAngle;
	}

	//////////////////
	///   Fields   ///
public:

	float X;
	float Y;
	float Z;
	float W;

	///////////////////
	///   Methods   ///
public:

	/** Formats this Quat as a String */
	FORCEINLINE String ToString() const
	{
		return Format("<@, @, @, @>", X, Y, Z, W);
	}

	/** Rotate this quaternion around an axis by a certain angle */
	FORCEINLINE void RotateByAxisAngle(const Vec3& axis, float angle, bool local)
	{
		// Construct a quaternion from the axis and angle
		Quat rotation(axis, angle);

		if (local)
		{
			// Perform a local rotation
			self = rotation * self;
		}
		else
		{
			// Perform a global rotation
			self = self * rotation;
		}
	}

	/////////////////////
	///   Operators   ///
public:

	friend FORCEINLINE Quat operator*(const Quat& lhs, const Quat& rhs)
	{
		Quat total;
		total.W = lhs.W * rhs.W - lhs.X * rhs.X - lhs.Y * rhs.Y - lhs.Z * rhs.Z;
		total.X = lhs.W * rhs.X + lhs.X * rhs.W + lhs.Y * rhs.Z - lhs.Z * rhs.Y;
		total.Y = lhs.W * rhs.Y - lhs.X * rhs.Z + lhs.Y * rhs.W + lhs.Z * rhs.X;
		total.Z = lhs.W * rhs.Z + lhs.X * rhs.Y - lhs.Y * rhs.X + lhs.Z * rhs.W;

		return total;
	}
	friend FORCEINLINE Quat& operator*=(Quat& lhs, const Quat& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}
	friend FORCEINLINE bool operator==(const Quat& lhs, const Quat& rhs)
	{
		return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z;
	}
	friend FORCEINLINE bool operator!=(const Quat& lhs, const Quat& rhs)
	{
		return lhs.X != rhs.X || lhs.Y != rhs.Y || lhs.Z != rhs.Z;
	}
};