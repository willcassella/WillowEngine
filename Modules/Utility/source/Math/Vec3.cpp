// Vec3.cpp

#include <cmath>
#include "..\..\include\Utility\Math\Vec3.h"
using namespace Willow;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(Willow::Vec3)
HAS_FACTORY
FIELD(X)
FIELD(Y)
FIELD(Z)
END_REFLECTION_INFO

////////////////////////
///   Constructors   ///

Vec3::Vec3(float x, float y, float z)
{
	this->X = x; this->Y = y; this->Z = z;
}

///////////////////
///   Methods   ///

float Vec3::Length() const
{
	return std::sqrtf(X * X + Y * Y + Z * Z);
}

Vec3 Vec3::Normalize() const
{
	float length = this->Length();
	return Vec3(X / length, Y / length, Z / length);
}

Vec3 Vec3::Cross(const Vec3& a, const Vec3& b)
{
	Vec3 result;
	result.X = a.Y * b.Z - a.Z * b.Y;
	result.Y = a.Z * b.X - a.X * b.Z;
	result.Z = a.Z * b.Y - a.Y * b.X;
	return result;
}

float Vec3::Dot(const Vec3& a, const Vec3& b)
{
	return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
}

float Vec3::Angle(const Vec3& a, const Vec3& b)
{
	return std::acos(Vec3::Dot(a.Normalize(), b.Normalize()));
}

String Vec3::ToString() const
{
	return String::Format("<@, @, @>", X, Y, Z);
}

////////////////////////////
///   Static Instances   ///

const Vec3 Vec3::Zero = Vec3(0, 0, 0);
const Vec3 Vec3::Up = Vec3(0, 1, 0);
const Vec3 Vec3::Forward = Vec3(0, 0, -1);
const Vec3 Vec3::Right = Vec3(1, 0, 0);

/////////////////////
///   Operators   ///

Vec3 Willow::operator+(const Vec3& lhs, const Vec3& rhs)
{
	return Vec3(lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z);
}

Vec3& Willow::operator+=(Vec3& lhs, const Vec3& rhs)
{
	lhs = lhs + rhs;
	return lhs;
}

Vec3 Willow::operator-(const Vec3& lhs, const Vec3& rhs)
{
	return Vec3(lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z);
}

Vec3& Willow::operator-=(Vec3& lhs, const Vec3& rhs)
{
	lhs = lhs - rhs;
	return lhs;
}

Vec3 Willow::operator*(const Vec3& lhs, float rhs)
{
	return Vec3(lhs.X * rhs, lhs.Y * rhs, lhs.Z * rhs);
}

Vec3 Willow::operator*(float lhs, const Vec3& rhs)
{
	return Vec3(rhs.X * lhs, rhs.Y * lhs, rhs.Z * lhs);
}

Vec3& Willow::operator*=(Vec3& lhs, float rhs)
{
	lhs = lhs * rhs;
	return lhs;
}

Vec3 Willow::operator*(const Vec3& lhs, int32 rhs)
{
	return Vec3(lhs.X * rhs, lhs.Y * rhs, lhs.Z * rhs);
}

Vec3 Willow::operator*(int32 lhs, const Vec3& rhs)
{
	return Vec3(rhs.X * lhs, rhs.Y * lhs, rhs.Z * lhs);
}

Vec3& Willow::operator*=(Vec3& lhs, int32 rhs)
{
	lhs = lhs * rhs;
	return lhs;
}