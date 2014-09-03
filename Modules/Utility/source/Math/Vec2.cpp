// Vec2.cpp

#include "..\..\include\Utility\Math\Vec2.h"
using namespace Math;

////////////////////////
///   Constructors   ///

Vec2::Vec2(float _x, float _y)
{
	this->x = _x; this->y = _y;
}

///////////////////
///   Methods   ///

// Returns the length of this vector
float Vec2::length() const
{
	return std::sqrtf(x*x + y*y);
}

// Returns the normal of this vector
Vec2 Vec2::normalize() const
{
	float length = this->length();
	return Vec2(x / length, y / length);
}

// Calculates the dot product of this and another vector
float Vec2::dot(const Vec2& a, const Vec2& b)
{
	return a.x * b.x + a.y * b.y;
}

// Calculates the angle between two vectors
float Vec2::angle(const Vec2& a, const Vec2& b)
{
	return std::acos(Vec2::dot(a.normalize(), b.normalize()));
}

////////////////////////////
///   Static Instances   ///

const Vec2 Vec2::ZERO = Vec2(0, 0);
const Vec2 Vec2::UP = Vec2(0, 1);
const Vec2 Vec2::RIGHT = Vec2(1, 0);

/////////////////////
///   Operators   ///

// Add another vector to this vector
Vec2 Vec2::operator+(const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

// Add this vector to another vector and copy the result
Vec2& Vec2::operator+=(const Vec2& rhs)
{
	*this = *this + rhs;
	return *this;
}

// Subtract another vector from this vector
Vec2 Vec2::operator-(const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

// Subtract another vector from this vector and copy the result
Vec2& Vec2::operator-=(const Vec2& rhs)
{
	*this = *this - rhs;
	return *this;
}

// Multiply this vector by a float
Vec2 Vec2::operator*(float rhs) const
{
	return Vec2(x*rhs, y*rhs);
}

Vec2 Vec2::operator*(int rhs) const
{
	return Vec2( x*rhs, y*rhs );
}