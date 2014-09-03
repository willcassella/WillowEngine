// Vec3.h
#pragma once

#include <cmath>
#include "..\config.h"

namespace Math
{
	struct CORE_API Vec3
	{
		//////////////////
		///   Fields   ///
	public:

		float x, y, z;

		////////////////////////
		///   Constructors   ///
	public:

		Vec3(float _x = 0, float _y = 0, float _z = 0);

		///////////////////
		///   Methods   ///
	public:

		// Returns the length of this vector
		float length() const;

		// Returns the normalized version of this vector
		Vec3 normalize() const;

		// Returns the dot product of vector a and vector b
		static float dot(const Vec3& a, const Vec3& b);

		// Returns the cross product of vector a and vector b
		static Vec3 cross(const Vec3& a, const Vec3& b);

		// Calculates the angle between two vectors
		static float angle(const Vec3& a, const Vec3& b);

		////////////////////////////
		///   Static Instances   ///
	public:

		static const Vec3 ZERO;
		static const Vec3 UP;
		static const Vec3 FORWARD;
		static const Vec3 RIGHT;

		/////////////////////
		///   Operators   ///
	public:

		// Adds this vector to another vector
		Vec3 operator+(const Vec3& rhs) const;

		// Adds this vector to another vector and copies the data
		Vec3& operator+=(const Vec3& rhs);

		// Subtracts another vector from this vector
		Vec3 operator-(const Vec3& rhs) const;

		// Subtracts another vector from this vector and copies the result
		Vec3& operator-=(const Vec3& rhs);

		// Multiply this vector by a float
		Vec3 operator*(float rhs) const;

		// @TODO: Impliment operator*=(float rhs)

		// Multiply this vector by an int @TODO: Investigate if this overload is necessary
		Vec3 operator*(const int rhs) const;

		// Returns TRUE if this vector is equvilent to another vector
		inline bool operator==(const Vec3& rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}

		// Returns TRUE if this vector is NOT equivilent to another vector
		inline bool operator!=(const Vec3& rhs) const
		{
			return x != rhs.x || y != rhs.y || z != rhs.z;
		}
	};
}