// Quat.h
#pragma once

#include "Vec3.h"

// @TODO: conversion to Euler angles, conversion to axis+angle, and rotation by Euler angles

namespace Willow
{
	struct UTILITY_API Quat
	{
		//////////////////
		///   Fields   ///
	public:

		float X, Y, Z, W;

		////////////////////////
		///   Constructors   ///

		Quat();
		/** Constructs a new Quaternion
		axis - the axis about which this rotation represents
		angle - the amount (in degrees) to rotate about axis */
		Quat(const Vec3& axis, float angle);

		///////////////////
		///   Methods   ///
	public:

		/** Rotate this quaternion around an axis by a certain angle */
		void RotateByAxisAngle(const Vec3& axis, float angle, bool local);

		/////////////////////
		///   Operators   ///

		friend UTILITY_API Quat operator*(const Quat& lhs, const Quat& rhs);
		friend UTILITY_API Quat& operator*=(Quat& lhs, const Quat& rhs);
		friend UTILITY_API inline bool operator==(const Quat& lhs, const Quat& rhs)
		{
			return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z;
		}
		friend UTILITY_API inline bool operator!=(const Quat& lhs, const Quat& rhs)
		{
			return lhs.X != rhs.X || lhs.Y != rhs.Y || lhs.Z != rhs.Z;
		}
	};
}