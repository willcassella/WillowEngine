#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Vec3.h"
#include "Quat.h"
#include "Mat4.h"

struct Transform
{
	// Data
	Vec3 local;
	Quat orientation;
	Vec3 scale;

	// Default constructor
	Transform()
	{
		local.x = 0; local.y = 0; local.z = 0;
		scale.x = 1; scale.y = 1; scale.z = 1;
		orientation.x = 1; orientation.y = 0; orientation.z = 0; orientation.w = 0;
	}
	
	// Returns the global position
	Vec3 getGlobal()
	{
		//TODO: add parenting support
		return local;
	}

	// Translates the object in local space
	void translateLocal( Vec3 localMovement )
	{
		localMovement = orientation.to_matrix() * localMovement;
		local += localMovement;
	}

	// Constructs the model matrix for this transform
	Mat4 getModel()
	{
		// Generate the translation matrix from the local position vector
		Mat4 translate (
			1, 0, 0, -local.x,
			0, 1, 0, -local.y,
			0, 0, 1, -local.z,
			0, 0, 0, 1 );
			
		// Generate the scale matrix from the local scale vector
		Mat4 scale (
			scale.x, 0, 0, 0,
			0, scale.y, 0, 0,
			0, 0, scale.z, 0,
			0, 0, 0, 1 );

		// Multiply them together
		return translate * orientation.to_matrix() * scale;
	}
};

#endif