#ifndef VEC3_H_
#define VEC3_H_

#include <cmath>

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
	float length() const
	{
		return std::sqrtf( x*x + y*y + z*z );
	}

	// Returns the normal of this vector
	Vec3 normalize() const
	{
		float length = this->length();
		return Vec3( x/length, y/length, z/length );
	}

	// Returns the cross product of vector a and vector b
	static Vec3 cross( const Vec3& a, const Vec3& b )
	{
		Vec3 result;
		result.x = a.y * b.z - a.z * b.y;
		result.y = a.z * b.x - a.x * b.z;
		result.z = a.x * b.y - a.y * b.x;
		return result;
	}

	// Returns the dot product of vector a and vector b
	static float dot( const Vec3& a, const Vec3& b )
	{
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}

	// Calculates the angle between two vectors
	static float angle( const Vec3& a, const Vec3& b )
	{
		Vec3 a_normalized = a.normalize();
		Vec3 b_normalized = b.normalize();

		return std::acos( Vec3::dot( a_normalized, b_normalized ) );
	}

	/////////////////////
	///   Overloads   ///
	/////////////////////

	// Adds this vector to another vector
	Vec3 operator+( const Vec3& rhs ) const
	{
		return Vec3( x + rhs.x, y + rhs.y, z + rhs.z );
	}

	// Adds this vector to another vector and copies the data
	void operator+=( const Vec3& rhs )
	{
		x += rhs.x; y += rhs.y; z+= rhs.z;
	}

	// Subtracts another vector from this vector
	Vec3 operator-( const Vec3& rhs ) const
	{
		return Vec3( x - rhs.x, y - rhs.y, z - rhs.z );
	}

	// Subtracts another vector from this vector and copies the result
	void operator-=( const Vec3& rhs )
	{
		x -= rhs.x; y -= rhs.y; z-= rhs.z;
	}

	// Returns TRUE if this vector is equvilent to another vector
	inline bool operator==( const Vec3& rhs ) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}

	// Returns TRUE if this vector is NOT equivilent to another vector
	inline bool operator!=( const Vec3& rhs ) const
	{
		return x != rhs.x || y != rhs.y || z != rhs.z;
	}
};

#endif