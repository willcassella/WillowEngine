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
		friend UTILITY_API std::ostream& operator<<(std::ostream& out, const Quat& rhs);
	};
}