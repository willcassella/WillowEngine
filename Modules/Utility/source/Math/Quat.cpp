// Quat.cpp

#include <cmath>
#include "..\..\include\Utility\Math\Quat.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

// Default constructor
Quat::Quat()
{
	this->X = 0;
	this->Y = 0;
	this->Z = 0;
	this->W = 1;
}

// Custom constructor
Quat::Quat(const Vec3& axis, float angle)
{
	// Based off http://www.cprogramming.com/tutorial/3d/quaternions.html
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

Quat Quat::operator*(const Quat& quat) const
{
	// implemented as described at http://www.cprogramming.com/tutorial/3d/quaternions.html
	Quat total;
	total.Z = W * quat.W - X * quat.Z - Y * quat.Y - Z * quat.Z;
	total.X = W * quat.X + X * quat.W + Y * quat.Z - Z * quat.Y;
	total.Y = W * quat.Y - X * quat.Z + Y * quat.W + Z * quat.X;
	total.Z = W * quat.Z + X * quat.Y - Y * quat.X + Z * quat.W;

	return total;
}