// Vec3.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Vec2.h"

struct CORE_API Vec3 final : SerializeableStruct<Vec3>
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	////////////////////////
	///   Constructors   ///
public:

	constexpr Vec3()
		: X(0), Y(0), Z(0)
	{
		// All done
	}
	constexpr Vec3(Scalar x, Scalar y, Scalar z)
		: X(x), Y(y), Z(z)
	{
		// All done
	}
	constexpr Vec3(const Vec2& xy, Scalar z)
		: X(xy.X), Y(xy.Y), Z(z)
	{
		// All done
	}
	constexpr Vec3(Scalar x, const Vec2& yz)
		: X(x), Y(yz.X), Z(yz.Y)
	{
		// All done
	}

	//////////////////
	///   Fields   ///
public:

	Scalar X;
	Scalar Y;
	Scalar Z;

	///////////////////
	///   Methods   ///
public:

	/** Formats this Vec3 as a String */
	FORCEINLINE String ToString() const
	{
		return Format("<@, @, @>", X, Y, Z);
	}

	/** Returns the length of this vector */
	FORCEINLINE Scalar Length() const
	{
		return std::sqrt(X * X + Y * Y + Z * Z);
	}

	/** Returns the normalized version of this vector */
	FORCEINLINE Vec3 Normalize() const
	{
		auto length = Length();

		if (length != 0)
		{
			return Vec3(X / length, Y / length, Z / length);
		}
		else
		{
			return Vec3(0, 0, 0);
		}
	}

	FORCEINLINE Vec3 Reflect(const Vec3& vec) const
	{
		return 2 * Dot(*this, vec) * *this - vec;
	}

	/** Returns the dot product of two vectors */
	FORCEINLINE static Scalar Dot(const Vec3& a, const Vec3& b)
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
	FORCEINLINE static Scalar Angle(const Vec3& a, const Vec3& b)
	{
		return std::acos(Vec3::Dot(a.Normalize(), b.Normalize()));
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

	friend FORCEINLINE Vec3 operator+(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z);
	}
	friend FORCEINLINE Vec3 operator+(const Vec3& lhs, Scalar rhs)
	{
		return Vec3(lhs.X + rhs, lhs.Y + rhs, lhs.Z + rhs);
	}
	friend FORCEINLINE Vec3 operator+(Scalar lhs, const Vec3& rhs)
	{
		return Vec3(lhs + rhs.X, lhs + rhs.Y, lhs + rhs.Z);
	}
	friend FORCEINLINE Vec3& operator+=(Vec3& lhs, const Vec3& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}
	friend FORCEINLINE Vec3& operator+=(Vec3& lhs, Scalar rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}
	friend FORCEINLINE Vec3 operator-(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z);
	}
	friend FORCEINLINE Vec3 operator-(const Vec3& lhs, Scalar rhs)
	{
		return Vec3(lhs.X - rhs, lhs.Y - rhs, lhs.Z - rhs);
	}
	friend FORCEINLINE Vec3 operator-(Scalar lhs, const Vec3& rhs)
	{
		return Vec3(lhs - rhs.X, lhs - rhs.Y, lhs - rhs.Z);
	}
	friend FORCEINLINE Vec3& operator-=(Vec3& lhs, const Vec3& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}
	friend FORCEINLINE Vec3& operator-=(Vec3& lhs, Scalar rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}
	friend FORCEINLINE Vec3 operator*(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.X * rhs.X, lhs.Y * rhs.Y, lhs.Z * rhs.Z);
	}
	friend FORCEINLINE Vec3 operator*(const Vec3& lhs, Scalar rhs)
	{
		return Vec3(lhs.X * rhs, lhs.Y * rhs, lhs.Z * rhs);
	}
	friend FORCEINLINE Vec3 operator*(Scalar lhs, const Vec3& rhs)
	{
		return Vec3(lhs * rhs.X, lhs * rhs.Y, lhs * rhs.Z);
	}
	friend FORCEINLINE Vec3& operator*=(Vec3& lhs, const Vec3& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}
	friend FORCEINLINE Vec3& operator*=(Vec3& lhs, Scalar rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}
	friend FORCEINLINE Vec3 operator/(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.X / rhs.X, lhs.Y / rhs.Y, lhs.Z / rhs.Z);
	}
	friend FORCEINLINE Vec3 operator/(const Vec3& lhs, Scalar rhs)
	{
		return Vec3(lhs.X / rhs, lhs.Y / rhs, lhs.Z / rhs);
	}
	friend FORCEINLINE Vec3 operator/(Scalar lhs, const Vec3& rhs)
	{
		return Vec3(lhs / rhs.X, lhs / rhs.Y, lhs / rhs.Z);
	}
	friend FORCEINLINE Vec3& operator/=(Vec3& lhs, const Vec3& rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}
	friend FORCEINLINE Vec3& operator/=(Vec3& lhs, Scalar rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}
	friend FORCEINLINE bool operator==(const Vec3& lhs, const Vec3& rhs)
	{
		return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z;
	}
	friend FORCEINLINE bool operator!=(const Vec3& lhs, const Vec3& rhs)
	{
		return lhs.X != rhs.X || lhs.Y != rhs.Y || lhs.Z != rhs.Z;
	}
};
