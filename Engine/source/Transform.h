#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Vec3.h"
#include "Quat.h"
#include "Mat4.h"

struct Transform
{
	////////////////
	///   Data   ///
	////////////////
public:

	Vec3 position;
	Vec3 scale;
	Quat orientation;
	Transform* parent;
	
	////////////////////////
	///   Constructors   ///
	////////////////////////
public:

	// Default constructor
	Transform()
	{
		// Set scale to 1 (default for vec3 is 0)
		scale = Vec3( 1, 1, 1 );
		parent = nullptr;
	}

	// Custom constructor
	Transform( Vec3 _POSITION, Vec3 _SCALE, Quat _ORIENTATION )
	{
		position = _POSITION;
		scale = _SCALE;
		orientation = _ORIENTATION;
		parent = nullptr;
	}

	///////////////////
	///   Methods   ///
	///////////////////
public:

	// Translate this object in local or global space
	void translate( const Vec3& vec, const bool isLocal )
	{
		Vec3 translateVec = vec;
		if( isLocal ) {
			translateVec = Mat4::rotate( this->orientation ) * translateVec;
		}
		position += translateVec;
	}

	// Scale the object in local or global space
	void changeScale( const Vec3& vec, const bool isLocal )
	{
		Vec3 scaleVec = vec;
		if( isLocal ) {
			scaleVec = Mat4::rotate( this->orientation ) * scaleVec;
		}
		scale += scaleVec;
	}

	// Rotate the object by axis+angle in local or global space
	void rotate( const Vec3& axis, const float angle, const bool isLocal )
	{
		orientation.rotateByAxisAngle( axis, angle, isLocal );
	}

	// Constructs the model matrix for this transform
	Mat4 getModel()
	{
		// Generate the transformation matrices and multiply them together
		if( parent != nullptr ) {
			return this->parent->getModel() * (Mat4::translate( this->position) * Mat4::rotate( this->orientation ) * Mat4::scale( this->scale ));
		} else {
			return Mat4::translate( this->position ) * Mat4::rotate( this->orientation ) * Mat4::scale( this->scale );
		}
	}
};

#endif