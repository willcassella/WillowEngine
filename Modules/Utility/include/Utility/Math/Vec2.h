// Vec2.h
#pragma once

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

		// Returns the length of this vector
		float Length() const;

		// Returns the normalized version of this vector
		Vec2 Normalize() const;

		// Calculates the dot product of this and another vector
		static float Dot(const Vec2& a, const Vec2& b);

		// @TODO: Add cross product

		// Calculates the angle between two vectors
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

		// Add another vector to this vector
		Vec2 operator+(const Vec2& rhs) const;

		// Add this vector to another vector and copy the result
		Vec2& operator+=(const Vec2& rhs);

		// Subtract another vector from this vector
		Vec2 operator-(const Vec2& rhs) const;

		// Subtract another vector from this vector and copy the result
		Vec2& operator-=(const Vec2& rhs);

		// Multiply this vector by a float
		Vec2 operator*(float rhs) const;

		// @TODO: impliment operator*=(float rhs)

		// Multiply this vector by an int @TODO: investigate if this is necessary, with the above operator
		Vec2 operator*(int rhs) const;

		// @TODO: impliment operator*=(int rhs)

		// Returns TRUE if this vector is equivalent to another vector
		inline bool operator==(const Vec2& rhs) const
		{
			return X == rhs.X && Y == rhs.Y;
		}

		// Returns TRUE of this vector is NOT equivalent to another vector
		inline bool operator!=(const Vec2& rhs) const
		{
			return X != rhs.X || Y != rhs.Y;
		}
	};
}