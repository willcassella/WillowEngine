// Vec2.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <cmath>
#include "config.h"

struct MATH_API Vec2 final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;

	////////////////////////
	///   Constructors   ///
public:

	Vec2()
		: X(0.f), Y(0.f)
	{
		// All done
	}
	Vec2(float x, float y)
		: X(x), Y(y)
	{
		// All done
	}

	//////////////////
	///   Fields   ///
public:

	float X;
	float Y;

	///////////////////
	///   Methods   ///
public:

	/** Formats this Vec2 as a String */
	FORCEINLINE String ToString() const
	{
		return ::ToString("<@, @>", X, Y);
	}

	/** Returns the length of this vector */
	FORCEINLINE float Length() const
	{
		return sqrtf(X*X + Y*Y);
	}

	/** Returns the normalized version of this vector */
	FORCEINLINE Vec2 Normalize() const
	{
		float length = Length();
		return Vec2(X / length, Y / length);
	}
	
	/** Returns the dot product of two vectors */
	FORCEINLINE static float Dot(const Vec2& a, const Vec2& b)
	{
		return a.X * b.X + a.Y * b.Y;
	}

	/** Returns the angle between two vectors */
	FORCEINLINE static float Angle(const Vec2& a, const Vec2& b)
	{
		return acosf(Vec2::Dot(a.Normalize(), b.Normalize()));
	}

	////////////////////////////
	///   Static Instances   ///
public:

	static const Vec2 Zero;
	static const Vec2 Up;
	static const Vec2 Right;

	/////////////////////
	///   Operators   ///
public:

	friend MATH_API FORCEINLINE Vec2 operator+(const Vec2& lhs, const Vec2& rhs)
	{
		return Vec2(lhs.X + rhs.X, lhs.Y + rhs.Y);
	}
	friend MATH_API FORCEINLINE Vec2 operator+(const Vec2& lhs, float rhs)
	{
		return Vec2(lhs.X + rhs, lhs.Y + rhs);
	}
	friend MATH_API FORCEINLINE Vec2 operator+(float lhs, const Vec2& rhs)
	{
		return Vec2(lhs + rhs.X, lhs + rhs.Y);
	}
	friend MATH_API FORCEINLINE Vec2& operator+=(Vec2& lhs, const Vec2& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE Vec2& operator+=(Vec2& lhs, float rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE Vec2 operator-(const Vec2& lhs, const Vec2& rhs)
	{
		return Vec2(lhs.X - rhs.X, lhs.Y - rhs.Y);
	}
	friend MATH_API FORCEINLINE Vec2 operator-(const Vec2& lhs, float rhs)
	{
		return Vec2(lhs.X - rhs, lhs.Y - rhs);
	}
	friend MATH_API FORCEINLINE Vec2 operator-(float lhs, const Vec2& rhs)
	{
		return Vec2(lhs - rhs.X, lhs - rhs.Y);
	}
	friend MATH_API FORCEINLINE Vec2& operator-=(Vec2& lhs, const Vec2& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE Vec2& operator-=(Vec2& lhs, float rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE Vec2 operator*(const Vec2& lhs, const Vec2& rhs)
	{
		return Vec2(lhs.X * rhs.X, lhs.Y * rhs.Y);
	}
	friend MATH_API FORCEINLINE Vec2 operator*(const Vec2& lhs, float rhs)
	{
		return Vec2(lhs.X * rhs, lhs.Y * rhs);
	}
	friend MATH_API FORCEINLINE Vec2 operator*(float lhs, const Vec2& rhs)
	{
		return Vec2(lhs * rhs.X, lhs * rhs.Y);
	}
	friend MATH_API FORCEINLINE Vec2& operator*=(Vec2& lhs, const Vec2& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE Vec2& operator*=(Vec2& lhs, float rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE Vec2 operator/(const Vec2& lhs, const Vec2& rhs)
	{
		return Vec2(lhs.X / rhs.X, lhs.Y / rhs.Y);
	}
	friend MATH_API FORCEINLINE Vec2 operator/(const Vec2& lhs, float rhs)
	{
		return Vec2(lhs.X / rhs, lhs.Y / rhs);
	}
	friend MATH_API FORCEINLINE Vec2 operator/(float lhs, const Vec2& rhs)
	{
		return Vec2(lhs / rhs.X, lhs / rhs.Y);
	}
	friend MATH_API FORCEINLINE Vec2& operator/=(Vec2& lhs, const Vec2& rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE Vec2& operator/=(Vec2& lhs, float rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE bool operator==(const Vec2& lhs, const Vec2& rhs)
	{
		return lhs.X == rhs.X && lhs.Y == rhs.Y;
	}
	friend MATH_API FORCEINLINE bool operator!=(const Vec2& lhs, const Vec2& rhs)
	{
		return lhs.X != rhs.X || lhs.Y != rhs.Y;
	}
};