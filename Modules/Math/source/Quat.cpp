// Quat.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <cmath>
#include "../include/Math/Quat.h"

//////////////////////
///   Reflection   ///

STRUCT_REFLECTION(Quat)
.AddField("X", &Quat::X)
.AddField("Y", &Quat::Y)
.AddField("Z", &Quat::Z)
.AddField("W", &Quat::W);

////////////////////////
///   Constructors   ///

Quat::Quat()
	: X(0), Y(0), Z(0), W(0)
{
	// All done
}

Quat::Quat(const Vec3& axis, float angle)
{
	// Make sure the axis vector is normalized
	Vec3 normAxis = axis.Normalize();
	float sinHalfAngle = sinf(angle * 0.5f);

	W = cosf(angle / 2);
	X = normAxis.X * sinHalfAngle;
	Y = normAxis.Y * sinHalfAngle;
	Z = normAxis.Z * sinHalfAngle;
}

///////////////////
///   Methods   ///

String Quat::ToString() const
{
	return String::Format("<@, @, @, @>", X, Y, Z, W);
}

void Quat::RotateByAxisAngle(const Vec3& axis, float angle, bool local)
{
	// Construct a quaternion from the axis and angle
	Quat rotation(axis, angle);

	if (local) 
	{
		// Perform a local rotation
		This = rotation * This;
	}
	else 
	{
		// Perform a global rotation
		This  = This * rotation;
	}
}

String Quat::FromString(Quat& value, const String& string)
{
	return String::Parse("<@, @, @, @>", string, value.X, value.Y, value.Z, value.W);
}

/////////////////////
///   Operators   ///

Quat operator*(const Quat& lhs, const Quat& rhs)
{
	Quat total;
	total.W = lhs.W * rhs.W - lhs.X * rhs.X - lhs.Y * rhs.Y - lhs.Z * rhs.Z;
	total.X = lhs.W * rhs.X + lhs.X * rhs.W + lhs.Y * rhs.Z - lhs.Z * rhs.Y;
	total.Y = lhs.W * rhs.Y - lhs.X * rhs.Z + lhs.Y * rhs.W + lhs.Z * rhs.X;
	total.Z = lhs.W * rhs.Z + lhs.X * rhs.Y - lhs.Y * rhs.X + lhs.Z * rhs.W;

	return total;
}

Quat& operator*=(Quat& lhs, const Quat& rhs)
{
	lhs = lhs * rhs;
	return lhs;
}