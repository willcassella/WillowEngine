// Transform.h
#pragma once

#include "Vec3.h"
#include "Quat.h"
#include "Mat4.h"

namespace Math
{
	struct UTILITY_API Transform
	{
		//////////////////
		///   Fields   ///
	public:

		Vec3 position;
		Vec3 scale;
		Quat orientation;
		Transform* parent;

		////////////////////////
		///   Constructors   ///
	public:

		// Default constructor
		Transform();

		// Custom constructor
		Transform(const Vec3& _position, const Vec3& _scale, const Quat& _orientation);

		///////////////////
		///   Methods   ///
	public:

		// Translate this object in local or global space
		void translate(const Math::Vec3& vec, bool isLocal);
		
		// Scale the object in local or global space
		void changeScale(const Math::Vec3& vec, bool isLocal);

		// Rotate the object by axis+angle in local or global space
		void rotate(const Math::Vec3& axis, float angle, bool isLocal);

		// Constructs the model matrix for this transform
		Mat4 getModel() const;
	};
}