// Vec2.h
#pragma once

#include <cmath>
#include "..\config.h"

namespace Math
{
	struct UTILITY_API Vec2
	{
		//////////////////
		///   Fields   ///
	public:

		float x, y;

		////////////////////////
		///   Constructors   ///
	public:

		Vec2(float _x = 0, float _y = 0);

		///////////////////
		///   Methods   ///
	public:

		// Returns the length of this vector
		float length() const;

		// Returns the normalized version of this vector
		Vec2 normalize() const;

		// Calculates the dot product of this and another vector
		static float dot(const Vec2& a, const Vec2& b);

		// @TODO: Add cross product

		// Calculates the angle between two vectors
		static float angle(const Vec2& a, const Vec2& b);

		////////////////////////////
		///   Static Instances   ///
	public:

		static const Vec2 ZERO;
		static const Vec2 UP;
		static const Vec2 RIGHT;

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

		// Returns TRUE if this vector is equivilent to another vector
		inline bool operator==(const Vec2& rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}

		// Returns TRUE of this vector is NOT equivilent to another vector
		inline bool operator!=(const Vec2& rhs) const
		{
			return x != rhs.x || y != rhs.y;
		}
	};
}