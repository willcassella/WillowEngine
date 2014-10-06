// Vec3.h
#pragma once

#include "..\config.h"

namespace Willow
{
	struct UTILITY_API Vec3
	{
		//////////////////
		///   Fields   ///
	public:

		float X, Y, Z;

		////////////////////////
		///   Constructors   ///
	public:

		/** Constructs a new 3-length vector
		x - the x component of the vector
		y - the y component of the vector
		z - the z component of the vector */
		Vec3(float x = 0.f, float y = 0.f, float z = 0.f);

		///////////////////
		///   Methods   ///
	public:

		/** Returns the length of this vector */
		float Length() const;

		/** Returns the normalized version of this vector */
		Vec3 Normalize() const;

		/** Returns the dot product of two vectors */
		static float Dot(const Vec3& a, const Vec3& b);

		/** Returns the cross product of two vectors */
		static Vec3 Cross(const Vec3& a, const Vec3& b);

		/** Returns the angle between two vectors */
		static float Angle(const Vec3& a, const Vec3& b);

		////////////////////////////
		///   Static Instances   ///
	public:

		static const Vec3 Zero;
		static const Vec3 Up;
		static const Vec3 Forward;
		static const Vec3 Right;

		/////////////////////
		///   Operators   ///
	public:

		friend UTILITY_API Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
		friend UTILITY_API Vec3& operator+=(Vec3& lhs, const Vec3& rhs);
		friend UTILITY_API Vec3 operator-(const Vec3& lhs, const Vec3& rhs);
		friend UTILITY_API Vec3& operator-=(Vec3& lhs, const Vec3& rhs);
		friend UTILITY_API Vec3 operator*(const Vec3& lhs, float rhs);
		friend UTILITY_API Vec3 operator*(float lhs, const Vec3& rhs);
		friend UTILITY_API Vec3& operator*=(Vec3& lhs, float rhs);
		friend UTILITY_API Vec3 operator*(const Vec3& lhs, int32 rhs);
		friend UTILITY_API Vec3 operator*(int32 lhs, const Vec3& rhs);
		friend UTILITY_API Vec3& operator*=(Vec3& lhs, int32 rhs);
		friend UTILITY_API inline bool operator==(const Vec3& lhs, const Vec3& rhs)
		{
			return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z;
		}
		friend UTILITY_API inline bool operator!=(const Vec3& lhs, const Vec3& rhs)
		{
			return lhs.X != rhs.X || lhs.Y != rhs.Y || lhs.Z != rhs.Z;
		}
	};
}