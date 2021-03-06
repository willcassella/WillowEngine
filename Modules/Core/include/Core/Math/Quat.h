// Quat.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Vec3.h"
#include "Angle.h"

struct CORE_API Quat final : SerializeableStruct<Quat>
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	////////////////////////
	///   Constructors   ///
public:

	constexpr Quat()
		: X(0), Y(0), Z(0), W(1)
	{
		// All done
	}

	/** Performs a component-wise initialization of this Quat. */
	Quat(float x, float y, float z, float w)
		: X(x), Y(y), Z(z), W(w)
	{
		// All done
	}

	/** Constructs a new Quaternion
	* 'axis' - The axis about which this rotation represents
	* 'angle' - The amount to rotate about 'axis' */
	Quat(const Vec3& axis, Angle angle)
	{
		// Make sure the axis vector is normalized
		const auto normAxis = axis.Normalize();
		const auto sinHalfAngle = std::sin(angle * Scalar{ 0.5 });

		this->X = normAxis.X * sinHalfAngle;
		this->Y = normAxis.Y * sinHalfAngle;
		this->Z = normAxis.Z * sinHalfAngle;
		this->W = std::cos(angle * Scalar { 0.5 });
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

	/** Formats this Quat as a String */
	FORCEINLINE String ToString() const
	{
		return Format("<@, @, @, @>", X, Y, Z, W);
	}

	/** Rotate this quaternion around an axis by a certain angle */
	FORCEINLINE void RotateByAxisAngle(const Vec3& axis, Angle angle, bool local)
	{
		// Construct a quaternion from the axis and angle
		Quat rotation(axis, angle);

		if (local)
		{
			// Perform a local rotation
			*this = rotation * *this;
		}
		else
		{
			// Perform a global rotation
			*this = *this * rotation;
		}
	}

	/////////////////////
	///   Operators   ///
public:

	friend FORCEINLINE Quat operator*(const Quat& lhs, const Quat& rhs)
	{
		Quat total;
		total.W = lhs.W * rhs.W - lhs.X * rhs.X - lhs.Y * rhs.Y - lhs.Z * rhs.Z;
		total.X = lhs.W * rhs.X + lhs.X * rhs.W + lhs.Y * rhs.Z - lhs.Z * rhs.Y;
		total.Y = lhs.W * rhs.Y - lhs.X * rhs.Z + lhs.Y * rhs.W + lhs.Z * rhs.X;
		total.Z = lhs.W * rhs.Z + lhs.X * rhs.Y - lhs.Y * rhs.X + lhs.Z * rhs.W;

		return total;
	}
	friend FORCEINLINE Quat& operator*=(Quat& lhs, const Quat& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}
	friend FORCEINLINE bool operator==(const Quat& lhs, const Quat& rhs)
	{
		return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z;
	}
	friend FORCEINLINE bool operator!=(const Quat& lhs, const Quat& rhs)
	{
		return lhs.X != rhs.X || lhs.Y != rhs.Y || lhs.Z != rhs.Z;
	}
};
