#ifndef QUAT_H_
#define QUAT_H_

#include <cmath>
#include "object.h"
#include "Vec3.h"

// TODO: conversion to euler angles, conversion to axis+angle, and rotation by euler angles

struct Quat : public object
{
	REGISTER(Quat);

	////////////////////////
	///   Constructors   ///

	// Default constructor, initializes without rotation
	Quat();

	// Custom constructor
	Quat(const Vec3& axis, const float angle);

	////////////////
	///   Data   ///
private:

	// Quaternion data members should never be acessed directly from outside
	float x, y, z, w;

	///////////////////
	///   Methods   ///
public:

	// Rotate this quaternion by and axis and angle
	void rotateByAxisAngle( const Vec3& axis, const float angle, const bool local );

	// Returns the data members of this quaternion to external variables
	void retrieve( float* const X, float* const Y, float* const Z, float* const W ) const;

	/////////////////////
	///   Overloads   ///

	// Returns the quaternion result of one quaternion multiplied by another (rotation)
	Quat operator*( const Quat& quat );

	// Returns TRUE if this quaternion is euqivilent to another quaternion
	inline bool operator==( const Quat& rhs ) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
	}

	// Returns TRUE if this quaternion is NOT equivilent to another quaternions
	inline bool operator!=( const Quat& rhs ) const
	{
		return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
	}
};

#endif