#ifndef VEC3_H_
#define VEC3_H_

#include <math.h>

struct Vec3
{
	////////////////
	///   Data   ///
	////////////////

	float x, y, z;

	////////////////////////
	///   Constructors   ///
	////////////////////////

	// Default constructor
	Vec3()
	{
		x = 0; y = 0; z = 0;
	}

	// Custom constructor
	Vec3( float _X, float _Y, float _Z )
	{
		x = _X; y = _Y; z = _Z;
	}

	///////////////////
	///   Methods   ///
	///////////////////

	// Returns the length of this vector
	float length()
	{
		return sqrtf( x*x + y*y + z*z );
	}

	// Returns the normal of this vector
	Vec3 normal()
	{
		float length = this->length();
		return Vec3( x/length, y/length, z/length );
	}

	// Returns the cross product of vector a and vector b
	static Vec3 cross( Vec3 a, Vec3 b )
	{
		Vec3 result;
		result.x = a.y * b.z - a.z * b.y;
		result.y = a.z * b.x - a.x * b.z;
		result.z = a.x * b.y - a.y * b.x;
		return result;
	}

	// Returns the dot product of vector a and vector b
	static float dot( Vec3 a, Vec3 b )
	{
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}

	// Calculates the angle between two vectors
	static float angle( Vec3 a, Vec3 b )
	{
		Vec3 a_normalized = a.normal();
		Vec3 b_normalized = b.normal();

		return acos( Vec3::dot( a_normalized, b_normalized ) );
	}

	/////////////////////
	///   Overloads   ///
	/////////////////////

	// Copy another vector to this vector
	void operator=( Vec3 rhs )
	{
		x = rhs.x; y = rhs.y; z = rhs.z;
	}

	// Adds this vector to another vector
	Vec3 operator+( Vec3 rhs )
	{
		return Vec3( x + rhs.x, y + rhs.y, z + rhs.z );
	}

	// Adds this vector to another vector and copies the data
	void operator+=( Vec3 rhs )
	{
		x += rhs.x; y += rhs.y; z+= rhs.z;
	}

	// Subtracts another vector from this vector
	Vec3 operator-( Vec3 rhs )
	{
		return Vec3( x - rhs.x, y - rhs.y, z - rhs.z );
	}

	// Subtracts another vector from this vector and copies the result
	void operator-=( Vec3 rhs )
	{
		x -= rhs.x; y -= rhs.y; z-= rhs.z;
	}

	// Returns TRUE if this vector is equvilent to another vector
	bool operator==( Vec3 rhs )
	{
		if( x == rhs.x && y == rhs.y && z == rhs.z )
			return true;
		else
			return false;
	}

	// Returns TRUE if this vector is NOT equivilent to another vector
	bool operator!=( Vec3 rhs )
	{
		if( x != rhs.x || y != rhs.y || z != rhs.z )
			return true;
		else
			return false;
	}
};

#endif