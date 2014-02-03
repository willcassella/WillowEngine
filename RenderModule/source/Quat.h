#ifndef QUAT_H_
#define QUAT_H_

#include <math.h>
#include "Vec3.h"

// TODO: conversion to euler angles, conversion to axis+angle, and rotation by euler angles

struct Quat
{
	////////////////
	///   Data   ///
	////////////////
	
private:

	// Quaternion data members should never be acessed directly from outside
	float x, y, z, w;

	////////////////////////
	///   Constructors   ///
	////////////////////////
	
public:

	// Default constructor
	Quat()
	{
		x = 0; y = 0; z = 0; w = 1;
	}

	// Custom constructor
	Quat( Vec3 axis, float angle )
	{
		// Based off http://www.cprogramming.com/tutorial/3d/quaternions.html
		// Make sure the axis vector is normalized
		const Vec3 normAxis = axis.normal();
		w = cosf( angle/2 );
		x = normAxis.x * sinf( angle/2 );
		y = normAxis.y * sinf( angle/2 );
		z = normAxis.z * sinf( angle/2 );
	}

	///////////////////
	///   Methods   ///
	///////////////////

	// Rotate this quaternion by and axis and angle
	void rotateByAxisAngle( Vec3 axis, float angle, bool local )
	{
		// Construct a quaternion from the axis and angle
		Quat rotation( axis, angle );

		if( local )
			// Perform a local rotation
			*this = rotation * *this;
		else
			// Perform a global rotation
			*this  = *this * rotation;
	}

	// Returns the data members of this quaternion to external variables
	void retrieve( float* X, float* Y, float* Z, float* W )
	{
		*X = x; *Y = y; *Z = z; *W = w;
	}

	/////////////////////
	///   Overloads   ///
	/////////////////////

	// Copies another quaternion into this quaternion
	void operator=( Quat rhs )
	{
		x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w;
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

	// Returns TRUE if this quaternion is euqivilent to another quaternion
	bool operator==( Quat rhs )
	{
		return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
	}

	// Returns TRUE if this quaternion is NOT equivilent to another quaternions
	bool operator!=( Quat rhs )
	{
		return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
	}
};

#endif