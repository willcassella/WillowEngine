// Vec2.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <cmath>
#include "../Containers/String.h"
#include "../Reflection/Reflection.h"
#include "Math.h"

struct CORE_API Vec2 final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	////////////////////////
	///   Constructors   ///
public:

	constexpr Vec2()
		: X(0), Y(0)
	{
		// All done
	}
	constexpr Vec2(Scalar x, Scalar y)
		: X(x), Y(y)
	{
		// All done
	}

	//////////////////
	///   Fields   ///
public:

	Scalar X;
	Scalar Y;

	///////////////////
	///   Methods   ///
public:

	/** Formats this Vec2 as a String */
	FORCEINLINE String ToString() const
	{
		return Format("<@, @>", X, Y);
	}

	/** Returns the length of this vector */
	FORCEINLINE Scalar Length() const
	{
		return std::sqrt(X*X + Y*Y);
	}

	/** Returns the normalized version of this vector */
	FORCEINLINE Vec2 Normalize() const
	{
		auto length = Length();
		return Vec2(X / length, Y / length);
	}
	
	/** Returns the dot product of two vectors */
	FORCEINLINE static Scalar Dot(const Vec2& a, const Vec2& b)
	{
		return a.X * b.X + a.Y * b.Y;
	}

	/** Returns the angle between two vectors */
	FORCEINLINE static Scalar Angle(const Vec2& a, const Vec2& b)
	{
		return std::acos(Vec2::Dot(a.Normalize(), b.Normalize()));
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

	friend FORCEINLINE Vec2 operator+(const Vec2& lhs, const Vec2& rhs)
	{
		return Vec2(lhs.X + rhs.X, lhs.Y + rhs.Y);
	}
	friend FORCEINLINE Vec2 operator+(const Vec2& lhs, Scalar rhs)
	{
		return Vec2(lhs.X + rhs, lhs.Y + rhs);
	}
	friend FORCEINLINE Vec2 operator+(Scalar lhs, const Vec2& rhs)
	{
		return Vec2(lhs + rhs.X, lhs + rhs.Y);
	}
	friend FORCEINLINE Vec2& operator+=(Vec2& lhs, const Vec2& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}
	friend FORCEINLINE Vec2& operator+=(Vec2& lhs, Scalar rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}
	friend FORCEINLINE Vec2 operator-(const Vec2& lhs, const Vec2& rhs)
	{
		return Vec2(lhs.X - rhs.X, lhs.Y - rhs.Y);
	}
	friend FORCEINLINE Vec2 operator-(const Vec2& lhs, Scalar rhs)
	{
		return Vec2(lhs.X - rhs, lhs.Y - rhs);
	}
	friend FORCEINLINE Vec2 operator-(Scalar lhs, const Vec2& rhs)
	{
		return Vec2(lhs - rhs.X, lhs - rhs.Y);
	}
	friend FORCEINLINE Vec2& operator-=(Vec2& lhs, const Vec2& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}
	friend FORCEINLINE Vec2& operator-=(Vec2& lhs, Scalar rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}
	friend FORCEINLINE Vec2 operator*(const Vec2& lhs, const Vec2& rhs)
	{
		return Vec2(lhs.X * rhs.X, lhs.Y * rhs.Y);
	}
	friend FORCEINLINE Vec2 operator*(const Vec2& lhs, Scalar rhs)
	{
		return Vec2(lhs.X * rhs, lhs.Y * rhs);
	}
	friend FORCEINLINE Vec2 operator*(Scalar lhs, const Vec2& rhs)
	{
		return Vec2(lhs * rhs.X, lhs * rhs.Y);
	}
	friend FORCEINLINE Vec2& operator*=(Vec2& lhs, const Vec2& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}
	friend FORCEINLINE Vec2& operator*=(Vec2& lhs, Scalar rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}
	friend FORCEINLINE Vec2 operator/(const Vec2& lhs, const Vec2& rhs)
	{
		return Vec2(lhs.X / rhs.X, lhs.Y / rhs.Y);
	}
	friend FORCEINLINE Vec2 operator/(const Vec2& lhs, Scalar rhs)
	{
		return Vec2(lhs.X / rhs, lhs.Y / rhs);
	}
	friend FORCEINLINE Vec2 operator/(Scalar lhs, const Vec2& rhs)
	{
		return Vec2(lhs / rhs.X, lhs / rhs.Y);
	}
	friend FORCEINLINE Vec2& operator/=(Vec2& lhs, const Vec2& rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}
	friend FORCEINLINE Vec2& operator/=(Vec2& lhs, Scalar rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}
	friend FORCEINLINE bool operator==(const Vec2& lhs, const Vec2& rhs)
	{
		return lhs.X == rhs.X && lhs.Y == rhs.Y;
	}
	friend FORCEINLINE bool operator!=(const Vec2& lhs, const Vec2& rhs)
	{
		return lhs.X != rhs.X || lhs.Y != rhs.Y;
	}
};