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
};

#endif