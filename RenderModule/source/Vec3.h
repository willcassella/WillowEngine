#ifndef VEC3_H_
#define VEC3_H_

struct Vec3
{
	// Data
	float x, y, z;

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

	// Assignment operator
	void operator=( Vec3 rhs )
	{
		x = rhs.x; y = rhs.y; z = rhs.z;
	}

	// Addition operator
	Vec3 operator+( Vec3 rhs )
	{
		return Vec3( x + rhs.x, y + rhs.y, z + rhs.z );
	}

	// Addition-assignment operator
	void operator+=( Vec3 rhs )
	{
		x += rhs.x; y += rhs.y; z+= rhs.z;
	}

	// Subtraction operator
	Vec3 operator-( Vec3 rhs )
	{
		return Vec3( x - rhs.x, y - rhs.y, z - rhs.z );
	}

	// Subtraction-assignment operator
	void operator-=( Vec3 rhs )
	{
		x -= rhs.x; y -= rhs.y; z-= rhs.z;
	}

	// Equality operator
	bool operator==( Vec3 rhs )
	{
		if( x == rhs.x && y == rhs.y && z == rhs.z )
			return true;
		else
			return false;
	}

	// Inequality operator
	bool operator!=( Vec3 rhs )
	{
		if( x != rhs.x || y != rhs.y || z != rhs.z )
			return true;
		else
			return false;
	}
};

#endif