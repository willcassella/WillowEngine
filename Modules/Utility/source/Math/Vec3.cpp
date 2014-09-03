// Vec3.cpp

#include "..\..\include\Utility\Math\Vec3.h"
using namespace Math;

////////////////////////
///   Constructors   ///

Vec3::Vec3(float _x, float _y, float _z)
{
	this->x = _x; this->y = _z; this->z = _z;
}

///////////////////
///   Methods   ///

// Returns the length of this vector
float Vec3::length() const
{
	return std::sqrtf(x * x + y * y + z * z);
}

// Returns the normal of this vector
Vec3 Vec3::normalize() const
{
	float length = this->length();
	return Vec3(x / length, y / length, z / length);
}

// Returns the cross product of vector a and vector b
Vec3 Vec3::cross(const Vec3& a, const Vec3& b)
{
	Vec3 result;
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;
}

// Returns the dot product of vector a and vector b
float Vec3::dot(const Vec3& a, const Vec3& b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

// Calculates the angle between two vectors
float Vec3::angle(const Vec3& a, const Vec3& b)
{
	return std::acos(Vec3::dot(a.normalize(), b.normalize()));
}

////////////////////////////
///   Static Instances   ///

const Vec3 Vec3::ZERO = Vec3(0, 0, 0);
const Vec3 Vec3::UP = Vec3(0, 1, 0);
const Vec3 Vec3::FORWARD = Vec3(0, 0, -1);
const Vec3 Vec3::RIGHT = Vec3(1, 0, 0);

/////////////////////
///   Operators   ///

// Adds this vector to another vector
Vec3 Vec3::operator+(const Vec3& rhs) const
{
	return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
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
	return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
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
	return Vec3(x * rhs, y * rhs, z * rhs);
}

// Multiply this vector by an int
Vec3 Vec3::operator*(int rhs) const
{
	return Vec3(x*rhs, y*rhs, z*rhs);
}