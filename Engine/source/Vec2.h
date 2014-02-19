#ifndef VEC2_H_
#define VEC2_H_

#include <cmath>

struct Vec2
{
	////////////////
	///   Data   ///
	////////////////
public:

	float x, y;

	////////////////////////
	///   Constructors   ///
	////////////////////////
public:

	// Constructor, default set to 0
	Vec2( const float _X = 0, const float _Y = 0 );

	///////////////////
	///   Methods   ///
	///////////////////
public:

	// Returns the length of this vector
	float length() const;

	// Returns the normal of this vector
	Vec2 normalize() const;

	// Calculates the dot product of this and another vector
	static float dot( const Vec2& a, const Vec2& b );

	// Calculates the angle between two vectors
	static float angle( const Vec2& a, const Vec2& b );

	////////////////////////////
	///   Static Instances   ///
	////////////////////////////
public:

	static const Vec2 ZERO;
	static const Vec2 UP;
	static const Vec2 RIGHT;

	/////////////////////
	///   Overloads   ///
	/////////////////////
public:

	// Add another vector to this vector
	Vec2 operator+( const Vec2& rhs ) const;

	// Add this vector to another vector and copy the result
	void operator+=( const Vec2& rhs );

	// Subtract another vector from this vector
	Vec2 operator-( const Vec2& rhs ) const;

	// Subtract another vector from this vector and copy the result
	Vec2 operator-=( const Vec2& rhs );

	// Multiply this vector by a float
	Vec2 operator*( const float rhs ) const;

	// Multiply this vector by an int
	Vec2 operator*( const int rhs ) const;

	// Returns TRUE if this vector is equivilent to another vector
	inline bool operator==( const Vec2& rhs ) const
	{
		return x == rhs.x && y == rhs.y;
	}

	// Returns TRUE of this vector is NOT equivilent to another vector
	inline bool operator!=( const Vec2& rhs ) const
	{
		return x != rhs.x || y != rhs.y;
	}
};

#endif