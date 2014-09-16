// Vec2.cpp

#include <cmath>
#include "..\..\include\Utility\Math\Vec2.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

Vec2::Vec2(float x, float y)
{
	this->X = x; this->Y = y;
}

///////////////////
///   Methods   ///

// Returns the length of this vector
float Vec2::Length() const
{
	return std::sqrtf(X*X + Y*Y);
}

// Returns the normal of this vector
Vec2 Vec2::Normalize() const
{
	float length = this->Length();
	return Vec2(X / length, Y / length);
}

// Calculates the dot product of this and another vector
float Vec2::Dot(const Vec2& a, const Vec2& b)
{
	return a.X * b.X + a.Y * b.Y;
}

// Calculates the angle between two vectors
float Vec2::Angle(const Vec2& a, const Vec2& b)
{
	return std::acos(Vec2::Dot(a.Normalize(), b.Normalize()));
}

////////////////////////////
///   Static Instances   ///

const Vec2 Vec2::Zero = Vec2(0, 0);
const Vec2 Vec2::Up = Vec2(0, 1);
const Vec2 Vec2::Right = Vec2(1, 0);

/////////////////////
///   Operators   ///

// Add another vector to this vector
Vec2 Vec2::operator+(const Vec2& rhs) const
{
	return Vec2(X + rhs.X, Y + rhs.Y);
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
	return Vec2(X - rhs.X, Y - rhs.Y);
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
	return Vec2(X * rhs, Y * rhs);
}

Vec2 Vec2::operator*(int rhs) const
{
	return Vec2(X * rhs, Y * rhs);
}