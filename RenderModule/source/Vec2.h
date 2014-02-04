#ifndef VEC2_H_
#define VEC2_H_

#include <cmath>

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
	float length() const
	{
		return sqrtf( x*x + y*y );
	}

	// Returns the normal of this vector
	Vec2 normalize() const
	{
		float length = this->length();
		return Vec2( x/length, y/length );
	}

	// Calculates the dot product of this and another vector
	static float dot( const Vec2& a, const Vec2& b )
	{
		return a.x*b.x + a.y*b.y;
	}

	// Calculates the angle between two vectors
	static float angle( const Vec2& a, const Vec2& b )
	{
		Vec2 a_normalized = a.normalize();
		Vec2 b_normalized = b.normalize();

		return acos( Vec2::dot( a_normalized, b_normalized ) );
	}

	/////////////////////
	///   Overloads   ///
	/////////////////////

	// Add another vector to this vector
	Vec2 operator+( const Vec2& rhs ) const
	{
		return Vec2( x + rhs.x, y + rhs.y );
	}

	// Add this vector to another vector and copy the result
	void operator+=( const Vec2& rhs )
	{
		x += rhs.x; y += rhs.y ;
	}

	// Subtract another vector from this vector
	Vec2 operator-( const Vec2& rhs ) const
	{
		return Vec2( x - rhs.x, y - rhs.y );
	}

	// Subtract another vector from this vector and copy the result
	Vec2 operator-=( const Vec2& rhs )
	{
		x -= rhs.x; y -= rhs.y;
	}

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