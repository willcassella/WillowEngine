// Vec2.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"

struct MATH_API Vec2
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;

	////////////////////////
	///   Constructors   ///
public:

	/** Constructs a new 2-length vector */
	Vec2(float x = 0.f, float y = 0.f);

	//////////////////
	///   Fields   ///
public:

	float X;
	float Y;

	///////////////////
	///   Methods   ///
public:

	/** Formats this Vec2 as a String */
	String ToString() const;

	/** Returns the length of this vector */
	float Length() const;

	/** Returns the normalized version of this vector */
	Vec2 Normalize() const;

	/** Returns the dot product of two vectors */
	static float Dot(const Vec2& a, const Vec2& b);

	/** Returns the angle between two vectors */
	static float Angle(const Vec2& a, const Vec2& b);

	/** Parse a Vec2 from a String */
	static String FromString(Vec2& value, const String& string);

	////////////////////////////
	///   Static Instances   ///
public:

	static const Vec2 Zero;
	static const Vec2 Up;
	static const Vec2 Right;

	/////////////////////
	///   Operators   ///
public:

	friend MATH_API Vec2 operator+(const Vec2& lhs, const Vec2& rhs);
	friend MATH_API Vec2& operator+=(Vec2& lhs, const Vec2& rhs);
	friend MATH_API Vec2 operator-(const Vec2& lhs, const Vec2& rhs);
	friend MATH_API Vec2& operator-=(Vec2& lhs, const Vec2& rhs);
	friend MATH_API Vec2 operator*(const Vec2& lhs, float rhs);
	friend MATH_API Vec2 operator*(float lhs, const Vec2& rhs);
	friend MATH_API Vec2& operator*=(Vec2& lhs, float rhs);

	// @TODO: Are these necessary?
	friend MATH_API Vec2 operator*(const Vec2& lhs, int32 rhs);
	friend MATH_API Vec2 operator*(int32 lhs, const Vec2& rhs);
	friend MATH_API Vec2& operator*=(Vec2& lhs, int32 rhs);

	friend MATH_API inline bool operator==(const Vec2& lhs, const Vec2& rhs)
	{
		return lhs.X == rhs.X && lhs.Y == rhs.Y;
	}
	friend MATH_API inline bool operator!=(const Vec2& lhs, const Vec2& rhs)
	{
		return lhs.X != rhs.X || lhs.Y != rhs.Y;
	}
};