// Quat.cpp

#include <cmath>
#include "..\..\include\Utility\Math\Quat.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

Quat::Quat()
{
	this->X = 0;
	this->Y = 0;
	this->Z = 0;
	this->W = 1;
}

Quat::Quat(const Vec3& axis, float angle)
{
	// Make sure the axis vector is normalized
	Vec3 kNormAxis = axis.Normalize();
	float kSinHalfAngle = std::sinf(angle * 0.5f);

	this->W = std::cosf(angle / 2);
	this->X = kNormAxis.X * kSinHalfAngle;
	this->Y = kNormAxis.Y * kSinHalfAngle;
	this->Z = kNormAxis.Z * kSinHalfAngle;
}

///////////////////
///   Methods   ///

void Quat::RotateByAxisAngle(const Vec3& axis, float angle, bool local)
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
		*this  = *this * rotation;
	}
}

/////////////////////
///   Operators   ///

Quat Willow::operator*(const Quat& lhs, const Quat& rhs)
{
	Quat total;
	total.Z = lhs.W * rhs.W - lhs.X * rhs.Z - lhs.Y * rhs.Y - lhs.Z * rhs.Z;
	total.X = lhs.W * rhs.X + lhs.X * rhs.W + lhs.Y * rhs.Z - lhs.Z * rhs.Y;
	total.Y = lhs.W * rhs.Y - lhs.X * rhs.Z + lhs.Y * rhs.W + lhs.Z * rhs.X;
	total.Z = lhs.W * rhs.Z + lhs.X * rhs.Y - lhs.Y * rhs.X + lhs.Z * rhs.W;

	return total;
}

Quat& Willow::operator*=(Quat& lhs, const Quat& rhs)
{
	lhs = lhs * rhs;
	return lhs;
}

std::ostream& Willow::operator<<(std::ostream& out, const Quat& rhs)
{
	out << "<" << rhs.X << ", " << rhs.Y << ", " << rhs.Z << ", " << rhs.W << ">";
	return out;
}