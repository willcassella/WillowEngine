#ifndef VEC3_H_
#define VEC3_H_

#include <cmath>

struct Vec3
{
	////////////////
	///   Data   ///
	////////////////
public:

	float x, y, z;

	////////////////////////
	///   Constructors   ///
	////////////////////////
public:

	// Constructor, default to 0
	Vec3( const float _X = 0, const float _Y = 0, const float _Z = 0 );

	///////////////////
	///   Methods   ///
	///////////////////
public:

	// Returns the length of this vector
	float length() const;

	// Returns the normal of this vector
	Vec3 normalize() const;

	// Returns the cross product of vector a and vector b
	static Vec3 cross( const Vec3& a, const Vec3& b );

	// Returns the dot product of vector a and vector b
	static float dot( const Vec3& a, const Vec3& b );

	// Calculates the angle between two vectors
	static float angle( const Vec3& a, const Vec3& b );

	////////////////////////////
	///   Static Instances   ///
	////////////////////////////
public:

	static const Vec3 ZERO;
	static const Vec3 UP;
	static const Vec3 FORWARD;
	static const Vec3 RIGHT;

	/////////////////////
	///   Overloads   ///
	/////////////////////
public:

	// Adds this vector to another vector
	Vec3 operator+( const Vec3& rhs ) const;

	// Adds this vector to another vector and copies the data
	void operator+=( const Vec3& rhs );

	// Subtracts another vector from this vector
	Vec3 operator-( const Vec3& rhs ) const;

	// Subtracts another vector from this vector and copies the result
	void operator-=( const Vec3& rhs );

	// Multiply this vector by a float
	Vec3 operator*( const float rhs ) const;

	// Multiply this vector by an int
	Vec3 operator*( const int rhs ) const;

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