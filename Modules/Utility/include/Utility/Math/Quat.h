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
		Quat(const Vec3& axis, float angle);

		///////////////////
		///   Methods   ///
	public:

		void RotateByAxisAngle(const Vec3& axis, float angle, bool local);

		/////////////////////
		///   Operators   ///

		Quat operator*(const Quat& quat) const;
		inline bool operator==(const Quat& rhs) const
		{
			return X == rhs.X && Y == rhs.Y && Z == rhs.Z && W == rhs.W;
		}
		inline bool operator!=(const Quat& rhs) const
		{
			return X != rhs.X || Y != rhs.Y || Z != rhs.Z || W != rhs.W;
		}
	};
}