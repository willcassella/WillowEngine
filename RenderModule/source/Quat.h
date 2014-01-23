#ifndef QUAT_H_
#define QUAT_H_

#include "Mat4.h"

struct Quat
{
	// Data
	float x, y, z, w;

	// Default constructor
	Quat()
	{
		x = 1; y = 0; z = 0; w = 0;
	}

	// Returns the quaternion result of one quaternion multiplied by another (rotation)
	Quat operator*( Quat quat )
	{
		// implimented as described at http://www.cprogramming.com/tutorial/3d/quaternions.html
		Quat total;
		total.w = w*quat.w - x*quat.x - y*quat.y - z*quat.z;
		total.x = w*quat.x + x*quat.w + y*quat.z - z*quat.y;
		total.y = w*quat.y - x*quat.z + y*quat.w + z*quat.x;
		total.z = w*quat.z + x*quat.y - y*quat.x + z*quat.w;

		return total;
	}

	// Turn this quaternion into a rotation matrix
	Mat4 to_matrix()
	{
		return Mat4(
			1 - 2*y*y - 2*z*z,	2*x*y + 2*z*w,		2*x*z - 2*y*w,		0,
			2*x*y - 2*z*w,		1 - 2*x*x - 2*z*z,	2*y*z + 2*x*w,		0,
			2*x*z + 2*y*w,		2*y*z - 2*x*w,		1 - 2*x*x - 2*y*y,	0,
			0,					0,					0,					1 );
	}
};

#endif