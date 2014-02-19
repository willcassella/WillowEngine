// Vec3.cpp

#include "Vec3.h"

////////////////////////
///   Constructors   ///
////////////////////////

// Constructor, default to 0
Vec3::Vec3( const float _X, const float _Y, const float _Z )
{
	this->x = _X; this->y = _Y; this->z = _Z;
}

///////////////////
///   Methods   ///
///////////////////

// Returns the length of this vector
float Vec3::length() const
{
	return std::sqrtf(x*x + y*y + z*z );
}

// Returns the normal of this vector
Vec3 Vec3::normalize() const
{
	const float length = this->length();
	return Vec3( x/length, y/length, z/length );
}

// Returns the cross product of vector a and vector b
Vec3 Vec3::cross( const Vec3& a, const Vec3& b )
{
	Vec3 result;
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;
}

// Returns the dot product of vector a and vector b
float Vec3::dot( const Vec3& a, const Vec3& b )
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

// Calculates the angle between two vectors
float Vec3::angle( const Vec3& a, const Vec3& b )
{
	const Vec3 a_normalized = a.normalize();
	const Vec3 b_normalized = b.normalize();

	return std::acos( Vec3::dot( a_normalized, b_normalized ) );
}

////////////////////////////
///   Static Instances   ///
////////////////////////////

const Vec3 Vec3::ZERO = Vec3( 0, 0, 0);
const Vec3 Vec3::UP = Vec3( 0, 1, 0 );
const Vec3 Vec3::FORWARD = Vec3( 0, 0, -1 );
const Vec3 Vec3::RIGHT = Vec3( 1, 0, 0 );

/////////////////////
///   Overloads   ///
/////////////////////

// Adds this vector to another vector
Vec3 Vec3::operator+( const Vec3& rhs ) const
{
	return Vec3( x + rhs.x, y + rhs.y, z + rhs.z );
}

// Adds this vector to another vector and copies the data
void Vec3::operator+=( const Vec3& rhs )
{
	x += rhs.x; y += rhs.y; z+= rhs.z;
}

// Subtracts another vector from this vector
Vec3 Vec3::operator-( const Vec3& rhs ) const
{
	return Vec3( x - rhs.x, y - rhs.y, z - rhs.z );
}

// Subtracts another vector from this vector and copies the result
void Vec3::operator-=( const Vec3& rhs )
{
	x -= rhs.x; y -= rhs.y; z-= rhs.z;
}

// Multiply this vector by a float
Vec3 Vec3::operator*( const float rhs ) const
{
	return Vec3( x*rhs, y*rhs, z*rhs );
}

// Multiply this vector by an int
Vec3 Vec3::operator*( const int rhs ) const
{
	return Vec3( x*rhs, y*rhs, z*rhs );
}