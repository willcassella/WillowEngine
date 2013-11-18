#ifndef QUATERNION_H_
#define QUATERNION_H_

struct Quaternion
{
	float x;
	float y;
	float z;
	float w;

	Quaternion operator*( Quaternion quat )
	{
		// implimented as described at http://www.cprogramming.com/tutorial/3d/quaternions.html
		Quaternion total;
		total.w = w*quat.w - x*quat.x - y*quat.y - z*quat.z;
		total.x = w*quat.x + x*quat.w + y*quat.z - z*quat.y;
		total.y = w*quat.y - x*quat.z + y*quat.w + z*quat.x;
		total.z = w*quat.z + x*quat.y - y*quat.x + z*quat.w;

		return total;
	}
};

#endif