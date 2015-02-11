// Vec3.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

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
	Vec3(float x = 0.f, float y = 0.f, float z = 0.f);

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
	String ToString() const;

	/** Returns the length of this vector */
	float Length() const;

	/** Returns the normalized version of this vector */
	Vec3 Normalize() const;

	/** Parse a Vec3 from a String */
	static String FromString(Vec3& value, const String& string);

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

	friend MATH_API Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
	friend MATH_API Vec3& operator+=(Vec3& lhs, const Vec3& rhs);
	friend MATH_API Vec3 operator-(const Vec3& lhs, const Vec3& rhs);
	friend MATH_API Vec3& operator-=(Vec3& lhs, const Vec3& rhs);
	friend MATH_API Vec3 operator*(const Vec3& lhs, float rhs);
	friend MATH_API Vec3 operator*(float lhs, const Vec3& rhs);
	friend MATH_API Vec3& operator*=(Vec3& lhs, float rhs);
	friend MATH_API Vec3 operator*(const Vec3& lhs, int32 rhs);
	friend MATH_API Vec3 operator*(int32 lhs, const Vec3& rhs);
	friend MATH_API Vec3& operator*=(Vec3& lhs, int32 rhs);
	friend MATH_API inline bool operator==(const Vec3& lhs, const Vec3& rhs)
	{
		return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z;
	}
	friend MATH_API inline bool operator!=(const Vec3& lhs, const Vec3& rhs)
	{
		return lhs.X != rhs.X || lhs.Y != rhs.Y || lhs.Z != rhs.Z;
	}
};