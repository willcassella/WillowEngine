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

		Vec3(float x = 0.f, float y = 0.f, float z = 0.f);

		///////////////////
		///   Methods   ///
	public:

		float Length() const;
		Vec3 Normalize() const;
		static float Dot(const Vec3& a, const Vec3& b);
		static Vec3 Cross(const Vec3& a, const Vec3& b);
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

		Vec3 operator+(const Vec3& rhs) const;
		Vec3& operator+=(const Vec3& rhs);
		Vec3 operator-(const Vec3& rhs) const;
		Vec3& operator-=(const Vec3& rhs);
		Vec3 operator*(float rhs) const;

		// @TODO: Impliment operator*=(float rhs)

		Vec3 operator*(const int rhs) const;
		inline bool operator==(const Vec3& rhs) const
		{
			return X == rhs.X && Y == rhs.Y && Z == rhs.Z;
		}
		inline bool operator!=(const Vec3& rhs) const
		{
			return X != rhs.X || Y != rhs.Y || Z != rhs.Z;
		}
	};
}