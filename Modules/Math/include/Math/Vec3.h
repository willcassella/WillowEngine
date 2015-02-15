// Vec3.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <cmath>
#include "config.h"

struct MATH_API Vec3
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;

	////////////////////////
	///   Constructors   ///
public:

	/** Constructs a new 3-length vector */
	Vec3(float x = 0.f, float y = 0.f, float z = 0.f)
		: X(x), Y(y), Z(z)
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

	/** Parse a Vec3 from a String */
	FORCEINLINE static String FromString(Vec3& value, const String& string)
	{
		return String::Parse(string, "<@, @, @>", value.X, value.Y, value.Z);
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
			a.Z * b.Y - a.Y * b.X
			);
	}

	/** Returns the angle between two vectors */
	FORCEINLINE static float Angle(const Vec3& a, const Vec3& b)
	{
		return acos(Vec3::Dot(a.Normalize(), b.Normalize()));
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
	friend MATH_API FORCEINLINE Vec3& operator+=(Vec3& lhs, const Vec3& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE Vec3 operator-(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z);
	}
	friend MATH_API FORCEINLINE Vec3& operator-=(Vec3& lhs, const Vec3& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE Vec3 operator*(const Vec3& lhs, float rhs)
	{
		return Vec3(lhs.X * rhs, lhs.Y * rhs, lhs.Z * rhs);
	}
	friend MATH_API FORCEINLINE Vec3 operator*(float lhs, const Vec3& rhs)
	{
		return Vec3(rhs.X * lhs, rhs.Y * lhs, rhs.Z * lhs);
	}
	friend MATH_API FORCEINLINE Vec3& operator*=(Vec3& lhs, float rhs)
	{
		lhs = lhs * rhs;
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