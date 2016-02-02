// Vec4.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Vec3.h"

struct CORE_API Vec4 final : SerializeableStruct<Vec4>
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	////////////////////////
	///   Constructors   ///
public:

	constexpr Vec4()
		: X(0.f), Y(0.f), Z(0.f), W(0.f)
	{
		// All done
	}
	constexpr Vec4(Scalar x, Scalar y, Scalar z, Scalar w)
		: X(x), Y(y), Z(z), W(w)
	{
		// All done
	}
	constexpr Vec4(const Vec3& xyz, Scalar w)
		: X(xyz.X), Y(xyz.Y), Z(xyz.Z), W(w)
	{
		// All done
	}
	constexpr Vec4(Scalar x, const Vec3& yzw)
		: X(x), Y(yzw.X), Z(yzw.Y), W(yzw.Z)
	{
		// All done
	}
	constexpr Vec4(const Vec2& xy, const Vec2& zw)
		: X(xy.X), Y(xy.Y), Z(zw.X), W(zw.Y)
	{
		// All done
	}
	constexpr Vec4(const Vec2& xy, Scalar z, Scalar w)
		: X(xy.X), Y(xy.Y), Z(z), W(w)
	{
		// All done
	}
	constexpr Vec4(Scalar x, const Vec2& yz, Scalar w)
		: X(x), Y(yz.X), Z(yz.Y), W(w)
	{
		// All done
	}
	constexpr Vec4(Scalar x, Scalar y, const Vec2& zw)
		: X(x), Y(y), Z(zw.X), W(zw.Y)
	{
		// All done
	}

	//////////////////
	///   Fields   ///
public:

	Scalar X;
	Scalar Y;
	Scalar Z;
	Scalar W;

	///////////////////
	///   Methods   ///
public:

	/** Formats this Vec4 as a String */
	FORCEINLINE String ToString() const
	{
		return Format("<@, @, @, @>", X, Y, Z, W);
	}

	/** Returns the length of this vector */
	FORCEINLINE Scalar Length() const
	{
		return std::sqrt(X * X + Y * Y + Z * Z + W * W);
	}

	/** Normalizes this vector */
	FORCEINLINE Vec4 Normalize() const
	{
		auto length = Length();
		return Vec4(X / length, Y / length, Z / length, W / length);
	}

	/** Returns the dot product of two Vec4s */
	FORCEINLINE static Scalar Dot(const Vec4& a, const Vec4& b)
	{
		return a.X * b.X + a.Y * b.Y + a.Z * b.Z + a.W * b.W;
	}

	/** Returns the angle between two radians */
	FORCEINLINE static Scalar Angle(const Vec4& a, const Vec4& b)
	{
		return std::acos(Vec4::Dot(a.Normalize(), b.Normalize()));
	}

	////////////////////////////
	///   Static Instances   ///
public:

	static const Vec4 Zero;

	/////////////////////
	///   Operators   ///
public:

	friend FORCEINLINE Vec4 operator+(const Vec4& lhs, const Vec4& rhs)
	{
		return Vec4(lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z, lhs.W + rhs.W);
	}
	friend FORCEINLINE Vec4 operator+(const Vec4& lhs, Scalar rhs)
	{
		return Vec4(lhs.X + rhs, lhs.Y + rhs, lhs.Z + rhs, lhs.W + rhs);
	}
	friend FORCEINLINE Vec4 operator+(Scalar lhs, const Vec4& rhs)
	{
		return Vec4(lhs + rhs.X, lhs + rhs.Y, lhs + rhs.Z, lhs + rhs.W);
	}
	friend FORCEINLINE Vec4& operator+=(Vec4& lhs, const Vec4& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}
	friend FORCEINLINE Vec4& operator+=(Vec4& lhs, Scalar rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}
	friend FORCEINLINE Vec4 operator-(const Vec4& lhs, const Vec4& rhs)
	{
		return Vec4(lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z, lhs.W - rhs.W);
	}
	friend FORCEINLINE Vec4 operator-(const Vec4& lhs, Scalar rhs)
	{
		return Vec4(lhs.X - rhs, lhs.Y - rhs, lhs.Z - rhs, lhs.W - rhs);
	}
	friend FORCEINLINE Vec4 operator-(Scalar lhs, const Vec4& rhs)
	{
		return Vec4(lhs - rhs.X, lhs - rhs.Y, lhs - rhs.Z, lhs - rhs.W);
	}
	friend FORCEINLINE Vec4& operator-=(Vec4& lhs, const Vec4& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}
	friend FORCEINLINE Vec4& operator-=(Vec4& lhs, Scalar rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}
	friend FORCEINLINE Vec4 operator*(const Vec4& lhs, const Vec4& rhs)
	{
		return Vec4(lhs.X * rhs.X, lhs.Y * rhs.Y, lhs.Z * rhs.Z, lhs.W * rhs.W);
	}
	friend FORCEINLINE Vec4 operator*(const Vec4& lhs, Scalar rhs)
	{
		return Vec4(lhs.X * rhs, lhs.Y * rhs, lhs.Z * rhs, lhs.W * rhs);
	}
	friend FORCEINLINE Vec4 operator*(Scalar lhs, const Vec4& rhs)
	{
		return Vec4(lhs * rhs.X, lhs * rhs.Y, lhs * rhs.Z, lhs * rhs.W);
	}
	friend FORCEINLINE Vec4& operator*=(Vec4& lhs, const Vec4& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}
	friend FORCEINLINE Vec4& operator*=(Vec4& lhs, Scalar rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}
	friend FORCEINLINE Vec4 operator/(const Vec4& lhs, const Vec4& rhs)
	{
		return Vec4(lhs.X * rhs.X, lhs.Y * rhs.Y, lhs.Z * rhs.Z, lhs.W * rhs.W);
	}
	friend FORCEINLINE Vec4 operator/(const Vec4& lhs, Scalar rhs)
	{
		return Vec4(lhs.X * rhs, lhs.Y * rhs, lhs.Z * rhs, lhs.W * rhs);
	}
	friend FORCEINLINE Vec4 operator/(Scalar lhs, const Vec4& rhs)
	{
		return Vec4(lhs / rhs.X, lhs / rhs.Y, lhs / rhs.Z, lhs / rhs.W);
	}
	friend FORCEINLINE Vec4& operator/=(Vec4& lhs, const Vec4& rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}
	friend FORCEINLINE Vec4& operator/=(Vec4& lhs, Scalar rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}
	friend FORCEINLINE bool operator==(const Vec4& lhs, const Vec4& rhs)
	{
		return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z && lhs.W == rhs.W;
	}
	friend FORCEINLINE bool operator!=(const Vec4& lhs, const Vec4& rhs)
	{
		return lhs.X != rhs.X || lhs.Y != rhs.Y || lhs.Z != rhs.Z || lhs.W != rhs.W;
	}
};