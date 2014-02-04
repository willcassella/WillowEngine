#ifndef QUAT_H_
#define QUAT_H_

#include <cmath>
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
	Quat( const Vec3& axis, float angle )
	{
		// Based off http://www.cprogramming.com/tutorial/3d/quaternions.html
		// Make sure the axis vector is normalized
		const Vec3 kNormAxis = axis.normalize();
		const float kSinHalfAngle = std::sinf( angle * 0.5f );

		w = std::cosf( angle/2 );
		x = kNormAxis.x * kSinHalfAngle;
		y = kNormAxis.y * kSinHalfAngle;
		z = kNormAxis.z * kSinHalfAngle;
	}

	///////////////////
	///   Methods   ///
	///////////////////

	// Rotate this quaternion by and axis and angle
	void rotateByAxisAngle( const Vec3& axis, float angle, bool local )
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
	void retrieve( float& X, float& Y, float& Z, float& W ) const
	{
		X = x; Y = y; Z = z; W = w;
	}

	/////////////////////
	///   Overloads   ///
	/////////////////////

	// Returns the quaternion result of one quaternion multiplied by another (rotation)
	Quat operator*( const Quat& quat )
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
	bool operator==( const Quat& rhs ) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
	}

	// Returns TRUE if this quaternion is NOT equivilent to another quaternions
	bool operator!=( const Quat& rhs ) const
	{
		return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
	}
};

#endif