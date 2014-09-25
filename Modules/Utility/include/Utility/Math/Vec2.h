// Vec2.h
#pragma once

#include <ostream>
#include "..\config.h"

namespace Willow
{
	struct UTILITY_API Vec2
	{
		//////////////////
		///   Fields   ///
	public:

		float X, Y;

		////////////////////////
		///   Constructors   ///
	public:

		Vec2(float x = 0.f, float y = 0.f);

		///////////////////
		///   Methods   ///
	public:

		/** Returns the length of this vector */
		float Length() const;

		/** Returns the normalized version of this vector */
		Vec2 Normalize() const;

		/** Returns the normalized version of this vector */
		static float Dot(const Vec2& a, const Vec2& b);

		// @TODO: Add cross product

		/** Calculates the angle between two vectors */
		static float Angle(const Vec2& a, const Vec2& b);

		////////////////////////////
		///   Static Instances   ///
	public:

		static const Vec2 Zero;
		static const Vec2 Up;
		static const Vec2 Right;

		/////////////////////
		///   Operators   ///
	public:

		friend UTILITY_API Vec2 operator+(const Vec2& lhs, const Vec2& rhs);
		friend UTILITY_API Vec2& operator+=(Vec2& lhs, const Vec2& rhs);
		friend UTILITY_API Vec2 operator-(const Vec2& lhs, const Vec2& rhs);
		friend UTILITY_API Vec2& operator-=(Vec2& lhs, const Vec2& rhs);
		friend UTILITY_API Vec2 operator*(const Vec2& lhs, float rhs);
		friend UTILITY_API Vec2 operator*(float lhs, const Vec2& rhs);
		friend UTILITY_API Vec2& operator*=(Vec2& lhs, float rhs);
		friend UTILITY_API Vec2 operator*(const Vec2& lhs, int32 rhs);
		friend UTILITY_API Vec2 operator*(int32 lhs, const Vec2& rhs);
		friend UTILITY_API Vec2& operator*=(Vec2& lhs, int32 rhs);
		friend UTILITY_API inline bool operator==(const Vec2& lhs, const Vec2& rhs)
		{
			return lhs.X == rhs.X && lhs.Y == rhs.Y;
		}
		friend UTILITY_API inline bool operator!=(const Vec2& lhs, const Vec2& rhs)
		{
			return lhs.X != rhs.X || lhs.Y != rhs.Y;
		}
		friend UTILITY_API std::ostream& operator<<(std::ostream& out, const Vec2& rhs);
	};
}