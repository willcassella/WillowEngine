// Mat4.h
#pragma once

#include <cstdio>
#include <cmath>
#include "..\config.h"
#include "Vec3.h"
#include "Quat.h"

// TODO: Add a lookat() function

namespace Math
{
	struct CORE_API Mat4
	{
		////////////////////////
		///   Constructors   ///
	public:

		// Constructor, default sets to identity matrix
		Mat4(float aa = 1, float ba = 0, float ca = 0, float da = 0,
			float ab = 0, float bb = 1, float cb = 0, float db = 0,
			float ac = 0, float bc = 0, float cc = 1, float dc = 0,
			float ad = 0, float bd = 0, float cd = 0, float dd = 1);

		///////////////////
		///   Methods   ///
	public:

		// Returns the inverse of this matrix
		Mat4 inverse() const;

		// Print the matrix to the console @TODO: Replace this with a << operator overload
		void display() const;

		// Generates a perspective projection matrix
		static Mat4 perspective(float hFOV, float vFOV, float zMin, float zMax);

		// Generates a persepctive projection matrix based off desired horizontal FOV and screen ratio
		static Mat4 perspectiveHFOV(float hFOV, float ratio, float zMin, float zMax);

		// Generates a perspective projection matrix based off the desired vertical FOV and screen ratio
		static Mat4 perspectiveVFOV(float vFOV, float ratio, float zMin, float zMax);

		// Generates an orthographic projection matrix
		static Mat4 orthographic(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);

		// Returns a translation matrix from a 3-length vector
		static Mat4 translate(const Vec3& vec);

		// Returns a scale matrix from a 3-length vector
		static Mat4 scale(const Vec3& vec);

		// Returns a rotation matrix from a quaternion
		static Mat4 rotate(const Quat& rot);

		///////////////////////////////
		///   Getters and Setters   ///

		// Get contents by row and column
		inline float get(unsigned int column, unsigned int row) const
		{
			return values[column][row];
		}

		// Set contents by row and column
		inline void set(unsigned int column, unsigned int row, float value)
		{
			values[column][row] = value;
		}

		/////////////////////
		///   Operators   ///
	public:

		// Multiply by another matrix
		Mat4 operator*(const Mat4& rhs) const;

		// Multiply by a 3-length vector
		Vec3 operator* (const Vec3& rhs) const;

		// Get contents as an array
		inline float* operator[](unsigned int index)
		{
			return values[index];
		}

		// Get contents as a const array
		inline const float* const operator[](unsigned int index) const
		{
			return values[index];
		}

		////////////////
		///   Data   ///
	private:

		float values[4][4];
	};
}