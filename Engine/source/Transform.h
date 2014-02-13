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
	void translate( Vec3 vec, bool isLocal )
	{
		if( isLocal )
		{
			vec = Mat4::rotate( orientation ) * vec;
		}

		position += vec;
	}

	// Scale the object in local or global space
	void changeScale( Vec3 vec, bool isLocal )
	{
		if( isLocal )
			vec = Mat4::rotate( orientation ) * vec;

		scale += vec;
	}

	// Rotate the object by axis+angle in local or global space
	void rotate( Vec3 axis, float angle, bool isLocal )
	{
		orientation.rotateByAxisAngle( axis, angle, isLocal );
	}

	// Constructs the model matrix for this transform
	Mat4 getModel()
	{
		// Generate the transformation matrices and multiply them together
		if( parent != nullptr ) {
			return parent->getModel() * (Mat4::translate( this->position ) * Mat4::rotate( this->orientation ) * Mat4::scale( this->scale ));
		} else {
		return Mat4::translate( this->position ) * Mat4::rotate( this->orientation ) * Mat4::scale( this->scale );
		}
	}
};

#endif