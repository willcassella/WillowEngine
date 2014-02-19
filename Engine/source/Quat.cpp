// Quat.cpp

#include "Quat.h"

////////////////////////
///   Constructors   ///
////////////////////////

// Default constructor
Quat::Quat()
{
	this->x = 0; this->y = 0; this->z = 0; this->w = 1;
}

// Custom constructor
Quat::Quat( const Vec3& axis, const float angle )
{
	// Based off http://www.cprogramming.com/tutorial/3d/quaternions.html
	// Make sure the axis vector is normalized
	const Vec3 kNormAxis = axis.normalize();
	const float kSinHalfAngle = std::sinf( angle * 0.5f );

	this->w = std::cosf( angle/2 );
	this->x = kNormAxis.x * kSinHalfAngle;
	this->y = kNormAxis.y * kSinHalfAngle;
	this->z = kNormAxis.z * kSinHalfAngle;
}

///////////////////
///   Methods   ///
///////////////////

// Rotate this quaternion by and axis and angle
void Quat::rotateByAxisAngle( const Vec3& axis, const float angle, const bool local )
{
	// Construct a quaternion from the axis and angle
	Quat rotation( axis, angle );

	if( local ) {
		// Perform a local rotation
		*this = rotation * *this;
	}
	else {
		// Perform a global rotation
		*this  = *this * rotation;
	}
}

// Returns the data members of this quaternion to external variables
void Quat::retrieve( float* const X, float* const Y, float* const Z, float* const W ) const
{
	*X = x; *Y = y; *Z = z; *W = w;
}

/////////////////////
///   Overloads   ///
/////////////////////

// Returns the quaternion result of one quaternion multiplied by another (rotation)
Quat Quat::operator*( const Quat& quat )
{
	// implimented as described at http://www.cprogramming.com/tutorial/3d/quaternions.html
	Quat total;
	total.w = w*quat.w - x*quat.x - y*quat.y - z*quat.z;
	total.x = w*quat.x + x*quat.w + y*quat.z - z*quat.y;
	total.y = w*quat.y - x*quat.z + y*quat.w + z*quat.x;
	total.z = w*quat.z + x*quat.y - y*quat.x + z*quat.w;

	return total;
}