// Vec2.cpp

#include <cmath>
#include "..\..\include\Utility\Math\Vec2.h"
using namespace Willow;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(Willow::Vec2)
HAS_FACTORY
FIELD(X)
FIELD(Y)
END_REFLECTION_INFO

////////////////////////
///   Constructors   ///

Vec2::Vec2(float x, float y)
{
	this->X = x; this->Y = y;
}

///////////////////
///   Methods   ///

float Vec2::Length() const
{
	return std::sqrtf(X*X + Y*Y);
}

Vec2 Vec2::Normalize() const
{
	float length = this->Length();
	return Vec2(X / length, Y / length);
}

float Vec2::Dot(const Vec2& a, const Vec2& b)
{
	return a.X * b.X + a.Y * b.Y;
}

float Vec2::Angle(const Vec2& a, const Vec2& b)
{
	return std::acos(Vec2::Dot(a.Normalize(), b.Normalize()));
}

String Vec2::ToString() const
{
	return String::Format("< @, @ >", X, Y);
}

////////////////////////////
///   Static Instances   ///

const Vec2 Vec2::Zero = Vec2(0, 0);
const Vec2 Vec2::Up = Vec2(0, 1);
const Vec2 Vec2::Right = Vec2(1, 0);

/////////////////////
///   Operators   ///

Vec2 Willow::operator+(const Vec2& lhs, const Vec2& rhs)
{
	return Vec2(lhs.X + rhs.X, lhs.Y + rhs.Y);
}

Vec2& Willow::operator+=(Vec2& lhs, const Vec2& rhs)
{
	lhs = lhs + rhs;
	return lhs;
}

Vec2 Willow::operator-(const Vec2& lhs, const Vec2& rhs)
{
	return Vec2(lhs.X - rhs.X, lhs.Y - rhs.Y);
}

Vec2& Willow::operator-=(Vec2& lhs, const Vec2& rhs)
{
	lhs = lhs - rhs;
	return lhs;
}

Vec2 Willow::operator*(const Vec2& lhs, float rhs)
{
	return Vec2(lhs.X * rhs, lhs.Y * rhs);
}

Vec2 Willow::operator*(float lhs, const Vec2& rhs)
{
	return Vec2(rhs.X * lhs, rhs.Y * lhs);
}

Vec2& Willow::operator*=(Vec2& lhs, float rhs)
{
	lhs = lhs * rhs;
	return lhs;
}

Vec2 Willow::operator*(const Vec2& lhs, int32 rhs)
{
	return Vec2(lhs.X * rhs, lhs.Y * rhs);
}

Vec2 Willow::operator*(int32 lhs, const Vec2& rhs)
{
	return Vec2(rhs.X * lhs, rhs.Y * lhs);
}

Vec2& Willow::operator*=(Vec2& lhs, int32 rhs)
{
	lhs = lhs * rhs;
	return lhs;
}