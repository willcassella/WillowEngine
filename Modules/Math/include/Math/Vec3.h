// Vec3.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Vec2.h"

struct MATH_API Vec3 final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;

	////////////////////////
	///   Constructors   ///
public:

	Vec3()
		: X(0.f), Y(0.f), Z(0.f)
	{
		// All done
	}
	Vec3(float x, float y, float z)
		: X(x), Y(y), Z(z)
	{
		// All done
	}
	Vec3(const Vec2& xy, float z)
		: X(xy.X), Y(xy.Y), Z(z)
	{
		// All done
	}
	Vec3(float x, const Vec2& yz)
		: X(x), Y(yz.X), Z(yz.Y)
	{
		// All done
	}

	//////////////////
	///   Fields   ///
public:

	float X;
	float Y;
	float Z;

	///////////////////
	///   Methods   ///
public:

	/** Formats this Vec3 as a String */
	FORCEINLINE String ToString() const
	{
		return String::Format("<@, @, @>", X, Y, Z);
	}

	/** Returns the length of this vector */
	FORCEINLINE float Length() const
	{
		return sqrtf(X * X + Y * Y + Z * Z);
	}

	/** Returns the normalized version of this vector */
	FORCEINLINE Vec3 Normalize() const
	{
		float length = Length();
		return Vec3(X / length, Y / length, Z / length);
	}

	/** Returns the dot product of two vectors */
	FORCEINLINE static float Dot(const Vec3& a, const Vec3& b)
	{
		return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
	}

	/** Returns the cross product of two vectors */
	FORCEINLINE static Vec3 Cross(const Vec3& a, const Vec3& b)
	{
		return Vec3(
			a.Y * b.Z - a.Z * b.Y,
			a.Z * b.X - a.X * b.Z,
			a.X * b.Y - a.Y * b.X
			);
	}

	/** Returns the angle between two vectors */
	FORCEINLINE static float Angle(const Vec3& a, const Vec3& b)
	{
		return acosf(Vec3::Dot(a.Normalize(), b.Normalize()));
	}

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

	friend MATH_API FORCEINLINE Vec3 operator+(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z);
	}
	friend MATH_API FORCEINLINE Vec3 operator+(const Vec3& lhs, float rhs)
	{
		return Vec3(lhs.X + rhs, lhs.Y + rhs, lhs.Z + rhs);
	}
	friend MATH_API FORCEINLINE Vec3 operator+(float lhs, const Vec3& rhs)
	{
		return Vec3(lhs + rhs.X, lhs + rhs.Y, lhs + rhs.Z);
	}
	friend MATH_API FORCEINLINE Vec3& operator+=(Vec3& lhs, const Vec3& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE Vec3& operator+=(Vec3& lhs, float rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE Vec3 operator-(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z);
	}
	friend MATH_API FORCEINLINE Vec3 operator-(const Vec3& lhs, float rhs)
	{
		return Vec3(lhs.X - rhs, lhs.Y - rhs, lhs.Z - rhs);
	}
	friend MATH_API FORCEINLINE Vec3 operator-(float lhs, const Vec3& rhs)
	{
		return Vec3(lhs - rhs.X, lhs - rhs.Y, lhs - rhs.Z);
	}
	friend MATH_API FORCEINLINE Vec3& operator-=(Vec3& lhs, const Vec3& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE Vec3& operator-=(Vec3& lhs, float rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE Vec3 operator*(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.X * rhs.X, lhs.Y * rhs.Y, lhs.Z * rhs.Z);
	}
	friend MATH_API FORCEINLINE Vec3 operator*(const Vec3& lhs, float rhs)
	{
		return Vec3(lhs.X * rhs, lhs.Y * rhs, lhs.Z * rhs);
	}
	friend MATH_API FORCEINLINE Vec3 operator*(float lhs, const Vec3& rhs)
	{
		return Vec3(lhs * rhs.X, lhs * rhs.Y, lhs * rhs.Z);
	}
	friend MATH_API FORCEINLINE Vec3& operator*=(Vec3& lhs, const Vec3& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE Vec3& operator*=(Vec3& lhs, float rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE Vec3 operator/(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.X / rhs.X, lhs.Y / rhs.Y, lhs.Z / rhs.Z);
	}
	friend MATH_API FORCEINLINE Vec3 operator/(const Vec3& lhs, float rhs)
	{
		return Vec3(lhs.X / rhs, lhs.Y / rhs, lhs.Z / rhs);
	}
	friend MATH_API FORCEINLINE Vec3 operator/(float lhs, const Vec3& rhs)
	{
		return Vec3(lhs / rhs.X, lhs / rhs.Y, lhs / rhs.Z);
	}
	friend MATH_API FORCEINLINE Vec3& operator/=(Vec3& lhs, const Vec3& rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE Vec3& operator/=(Vec3& lhs, float rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE bool operator==(const Vec3& lhs, const Vec3& rhs)
	{
		return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z;
	}
	friend MATH_API FORCEINLINE bool operator!=(const Vec3& lhs, const Vec3& rhs)
	{
		return lhs.X != rhs.X || lhs.Y != rhs.Y || lhs.Z != rhs.Z;
	}
};