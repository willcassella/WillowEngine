// Vec3.cpp

#include <cmath>
#include "..\..\include\Utility\Math\Vec3.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

Vec3::Vec3(float x, float y, float z)
{
	this->X = x; this->Y = z; this->Z = z;
}

///////////////////
///   Methods   ///

// Returns the length of this vector
float Vec3::Length() const
{
	return std::sqrtf(X * X + Y * Y + Z * Z);
}

// Returns the normal of this vector
Vec3 Vec3::Normalize() const
{
	float length = this->Length();
	return Vec3(X / length, Y / length, Z / length);
}

// Returns the cross product of vector a and vector b
Vec3 Vec3::Cross(const Vec3& a, const Vec3& b)
{
	Vec3 result;
	result.X = a.Y * b.Z - a.Z * b.Y;
	result.Y = a.Z * b.X - a.X * b.Z;
	result.Z = a.Z * b.Y - a.Y * b.X;
	return result;
}

// Returns the dot product of vector a and vector b
float Vec3::Dot(const Vec3& a, const Vec3& b)
{
	return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
}

// Calculates the angle between two vectors
float Vec3::Angle(const Vec3& a, const Vec3& b)
{
	return std::acos(Vec3::Dot(a.Normalize(), b.Normalize()));
}

////////////////////////////
///   Static Instances   ///

const Vec3 Vec3::Zero = Vec3(0, 0, 0);
const Vec3 Vec3::Up = Vec3(0, 1, 0);
const Vec3 Vec3::Forward = Vec3(0, 0, -1);
const Vec3 Vec3::Right = Vec3(1, 0, 0);

/////////////////////
///   Operators   ///

// Adds this vector to another vector
Vec3 Vec3::operator+(const Vec3& rhs) const
{
	return Vec3(X + rhs.X, Y + rhs.Y, Z + rhs.Z);
}

// Adds this vector to another vector and copies the data
Vec3& Vec3::operator+=(const Vec3& rhs)
{
	*this = *this + rhs;
	return *this;
}

// Subtracts another vector from this vector
Vec3 Vec3::operator-(const Vec3& rhs) const
{
	return Vec3(X - rhs.X, Y - rhs.Y, Z - rhs.Z);
}

// Subtracts another vector from this vector and copies the result
Vec3& Vec3::operator-=(const Vec3& rhs)
{
	*this = *this - rhs;
	return *this;
}

// Multiply this vector by a float
Vec3 Vec3::operator*(float rhs) const
{
	return Vec3(X * rhs, Y * rhs, Z * rhs);
}

// Multiply this vector by an int
Vec3 Vec3::operator*(int rhs) const
{
	return Vec3(X * rhs, Y * rhs, Z * rhs);
}