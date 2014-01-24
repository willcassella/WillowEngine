#ifndef VEC2_H_
#define VEC2_H_

struct Vec2
{
	// Data
	float x, y;

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

	// Assignment operator
	void operator=( Vec2 rhs )
	{
		x = rhs.x; y = rhs.y;
	}

	// Addition operator
	Vec2 operator+( Vec2 rhs )
	{
		return Vec2( x + rhs.x, y + rhs.y );
	}

	// Addition-assignment operator
	void operator+=( Vec2 rhs )
	{
		x += rhs.x; y += rhs.y ;
	}

	// Subtraction operator
	Vec2 operator-( Vec2 rhs )
	{
		return Vec2( x - rhs.x, y - rhs.y );
	}

	// Subtraction-assignment operator
	Vec2 operator-=( Vec2 rhs )
	{
		x -= rhs.x; y -= rhs.y;
	}

	// Equality operator
	bool operator==( Vec2 rhs )
	{
		if( x == rhs.x && y == rhs.y )
			return true;
		else
			return false;
	}

	// Inequality operator
	bool operator!=( Vec2 rhs )
	{
		if( x != rhs.x || y != rhs.y )
			return true;
		else
			return false;
	}
};

#endif