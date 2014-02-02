#ifndef VEC2_H_
#define VEC2_H_

#include <math.h>

// TODO: dot product and other stuff

struct Vec2
{
	////////////////
	///   Data   ///
	////////////////

	float x, y;

	////////////////////////
	///   Constructors   ///
	////////////////////////

	// Default constructor
	Vec2()
	{
		x = 0; y = 0;
	}

	// Custom constructor
	Vec2( float _X, float _Y )
	{
		x = _X; y = _Y;
	}

	///////////////////
	///   Methods   ///
	///////////////////

	// Returns the length of this vector
	float length()
	{
		return sqrtf( x*x + y*y );
	}

	// Returns the normal of this vector
	Vec2 normal()
	{
		float length = this->length();
		return Vec2( x/length, y/length );
	}

	/////////////////////
	///   Overloads   ///
	/////////////////////

	// Copy another vector to this vector
	void operator=( Vec2 rhs )
	{
		x = rhs.x; y = rhs.y;
	}

	// Add another vector to this vector
	Vec2 operator+( Vec2 rhs )
	{
		return Vec2( x + rhs.x, y + rhs.y );
	}

	// Add this vector to another vector and copy the result
	void operator+=( Vec2 rhs )
	{
		x += rhs.x; y += rhs.y ;
	}

	// Subtract another vector from this vector
	Vec2 operator-( Vec2 rhs )
	{
		return Vec2( x - rhs.x, y - rhs.y );
	}

	// Subtract another vector from this vector and copy the result
	Vec2 operator-=( Vec2 rhs )
	{
		x -= rhs.x; y -= rhs.y;
	}

	// Returns TRUE if this vector is equivilent to another vector
	bool operator==( Vec2 rhs )
	{
		if( x == rhs.x && y == rhs.y )
			return true;
		else
			return false;
	}

	// Returns TRUE of this vector is NOT equivilent to another vector
	bool operator!=( Vec2 rhs )
	{
		if( x != rhs.x || y != rhs.y )
			return true;
		else
			return false;
	}
};

#endif