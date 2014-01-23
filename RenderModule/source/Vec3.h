#ifndef VEC3_H_
#define VEC3_H_

#include "Mat4.h"

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

	// Returns the matrix transformation of this vector
	Mat4 translate()
	{
		return Mat4(
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1 );
	}
};

#endif