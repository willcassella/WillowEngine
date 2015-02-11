// Vec2.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <cmath>
#include "../include/Math/Vec2.h"

//////////////////////
///   Reflection   ///

STRUCT_REFLECTION(Vec2)
.AddField("X", &Vec2::X)
.AddField("Y", &Vec2::Y);

////////////////////////
///   Constructors   ///

Vec2::Vec2(float x, float y)
	: X(x), Y(y)
{
	// All done
}

///////////////////
///   Methods   ///

String Vec2::ToString() const
{
	return String::Format("<@, @>", X, Y);
}

float Vec2::Length() const
{
	return sqrtf(X*X + Y*Y);
}

Vec2 Vec2::Normalize() const
{
	float length = Length();
	return Vec2(X / length, Y / length);
}

float Vec2::Dot(const Vec2& a, const Vec2& b)
{
	return a.X * b.X + a.Y * b.Y;
}

float Vec2::Angle(const Vec2& a, const Vec2& b)
{
	return acos(Vec2::Dot(a.Normalize(), b.Normalize()));
}

String Vec2::FromString(Vec2& value, const String& string)
{
	return String::Parse("<@, @>", string, value.X, value.Y);
}

////////////////////////////
///   Static Instances   ///

const Vec2 Vec2::Zero = Vec2(0, 0);
const Vec2 Vec2::Up = Vec2(0, 1);
const Vec2 Vec2::Right = Vec2(1, 0);

/////////////////////
///   Operators   ///

Vec2 operator+(const Vec2& lhs, const Vec2& rhs)
{
	return Vec2(lhs.X + rhs.X, lhs.Y + rhs.Y);
}

Vec2& operator+=(Vec2& lhs, const Vec2& rhs)
{
	lhs = lhs + rhs;
	return lhs;
}

Vec2 operator-(const Vec2& lhs, const Vec2& rhs)
{
	return Vec2(lhs.X - rhs.X, lhs.Y - rhs.Y);
}

Vec2& operator-=(Vec2& lhs, const Vec2& rhs)
{
	lhs = lhs - rhs;
	return lhs;
}

Vec2 operator*(const Vec2& lhs, float rhs)
{
	return Vec2(lhs.X * rhs, lhs.Y * rhs);
}

Vec2 operator*(float lhs, const Vec2& rhs)
{
	return Vec2(rhs.X * lhs, rhs.Y * lhs);
}

Vec2& operator*=(Vec2& lhs, float rhs)
{
	lhs = lhs * rhs;
	return lhs;
}

Vec2 operator*(const Vec2& lhs, int32 rhs)
{
	return Vec2(lhs.X * rhs, lhs.Y * rhs);
}

Vec2 operator*(int32 lhs, const Vec2& rhs)
{
	return Vec2(rhs.X * lhs, rhs.Y * lhs);
}

Vec2& operator*=(Vec2& lhs, int32 rhs)
{
	lhs = lhs * rhs;
	return lhs;
}