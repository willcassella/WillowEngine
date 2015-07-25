// Mat4.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <cassert>
#include "Vec3.h"
#include "Quat.h"

const float Deg2Rad = 0.0174532925f;
const float Rad2Deg = 57.2957795f;

struct MATH_API Mat4 final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;

	////////////////////////
	///   Constructors   ///
public:

	/** Constructs a new 4x4 matrix
	default - identity matrix
	values - what to set each element of the matrix to */
	Mat4(	float aa = 1.f, float ba = 0.f, float ca = 0.f, float da = 0.f,
			float ab = 0.f, float bb = 1.f, float cb = 0.f, float db = 0.f,
			float ac = 0.f, float bc = 0.f, float cc = 1.f, float dc = 0.f,
			float ad = 0.f, float bd = 0.f, float cd = 0.f, float dd = 1.f)
	{
		_values[0][0] = aa; _values[1][0] = ba; _values[2][0] = ca; _values[3][0] = da;
		_values[0][1] = ab; _values[1][1] = bb; _values[2][1] = cb; _values[3][1] = db;
		_values[0][2] = ac; _values[1][2] = bc; _values[2][2] = cc; _values[3][2] = dc;
		_values[0][3] = ad; _values[1][3] = bd; _values[2][3] = cd; _values[3][3] = dd;
	}

	///////////////////
	///   Methods   ///
public:

	/** Formats this Mat4 as a String */
	FORCEINLINE String ToString() const
	{
		return ::ToString("[ @, @, @, @ ]\n"
						  "| @, @, @, @ |\n"
						  "| @, @, @, @ |\n"
						  "[ @, @, @, @ ]",
			_values[0][0], _values[1][0], _values[2][0], _values[3][0],
			_values[0][1], _values[1][1], _values[2][1], _values[3][1],
			_values[0][2], _values[1][2], _values[2][2], _values[3][2],
			_values[0][3], _values[1][3], _values[2][3], _values[3][3]);
	}

	/** Returns the inverse of this matrix */
	Mat4 Inverse() const;

	/** Generates a perspective projection matrix with the given properties */
	FORCEINLINE static Mat4 Perspective(float hFOV, float vFOV, float zMin, float zMax)
	{
		// Convert vertical and horizontal FOV to radians
		float RadHFOV = hFOV * Deg2Rad;
		float RadVFOV = vFOV * Deg2Rad;

		float xMax = tanf(RadHFOV * 0.5f) * zMin;
		float xMin = -xMax;

		float yMax = tanf(RadVFOV * 0.5f) * zMin;
		float yMin = -yMax;

		float width = xMax - xMin;
		float height = yMax - yMin;
		float depth = zMax - zMin;

		return Mat4(
			2*zMin/width,	0,				(xMax+xMin)/width,	0,
			0,				2*zMin/height,	(yMax+yMin)/height, 0,
			0,				0,				-(zMax+zMin)/depth, -2*zMax*zMin/depth,
			0,				0,				-1,					0);
	}

	/** Generates a perspective projection matrix with the following horizontal FOV */
	FORCEINLINE static Mat4 PerspectiveHFOV(float hFOV, float ratio, float zMin, float zMax)
	{
		// Convert hFOV to radians
		float RadHFOV = hFOV * Deg2Rad;
		float vFOV = Rad2Deg * 2 * atan(tan(RadHFOV * 0.5f) * 1 / ratio);

		return Perspective(hFOV, vFOV, zMin, zMax);
	}

	/** Generates a perspective projection matrix with the following vertical FOV */
	FORCEINLINE static Mat4 PerspectiveVFOV(float vFOV, float ratio, float zMin, float zMax)
	{
		// Convert the vFOV to radians
		float RadVFOV = vFOV * Deg2Rad;
		float hFOV = Rad2Deg * 2 * atan(tan(RadVFOV * 0.5f) * ratio);

		return Perspective(hFOV, vFOV, zMin, zMax);
	}

	/** Generates an orthographic projection matrix with the given properties */
	FORCEINLINE static Mat4 Orthographic(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
	{
		float width = xMax - xMin;
		float height = yMax - yMin;
		float depth = zMax - zMin;

		return Mat4(
			2 / width, 0, 0, -(xMax + xMin) / width,
			0, 2 / height, 0, -(yMax + yMin) / height,
			0, 0, -2 / depth, -(zMax + zMin) / depth,
			0, 0, 0, 1);
	}

	/** Generates a transformation matrix representing a translation */
	FORCEINLINE static Mat4 Translate(const Vec3& vec)
	{
		return Mat4(
			1, 0, 0, vec.X,
			0, 1, 0, vec.Y,
			0, 0, 1, vec.Z,
			0, 0, 0, 1);
	}

	/** Generates a transformation matrix representing a Scale */
	FORCEINLINE static Mat4 Scale(const Vec3& vec)
	{
		return Mat4(
			vec.X, 0, 0, 0,
			0, vec.Y, 0, 0,
			0, 0, vec.Z, 0,
			0, 0, 0, 1);
	}

	/** Generates a transformation matrix representing a rotation */
	FORCEINLINE static Mat4 Rotate(const Quat& rot)
	{
		float x, y, z, w;
		x = rot.X;
		y = rot.Y;
		z = rot.Z;
		w = rot.W;

		return Mat4(
			1 - 2 * y*y - 2 * z*z, 2 * x*y + 2 * z*w, 2 * x*z - 2 * y*w, 0,
			2 * x*y - 2 * z*w, 1 - 2 * x*x - 2 * z*z, 2 * y*z + 2 * x*w, 0,
			2 * x*z + 2 * y*w, 2 * y*z - 2 * x*w, 1 - 2 * x*x - 2 * y*y, 0,
			0, 0, 0, 1);
	}

	/** Gets the value at the specified column and row */
	FORCEINLINE float Get(uint32 column, uint32 row) const
	{
		assert(column < 4 && row < 4);
		return _values[column][row];
	}

	/** Sets the value at the specified column and row */
	FORCEINLINE void Set(uint32 column, uint32 row, float value)
	{
		assert(column < 4 && row < 4);
		_values[column][row] = value;
	}

	/////////////////////
	///   Operators   ///
public:

	FORCEINLINE float* operator[](uint32 index)
	{
		assert(index < 16);
		return _values[index];
	}
	FORCEINLINE const float* operator[](uint32 index) const
	{
		assert(index < 16);
		return _values[index];
	}
	friend MATH_API FORCEINLINE Mat4 operator*(const Mat4& lhs, const Mat4& rhs)
	{
		Mat4 total;

		// For each row
		for (uint32 row = 0; row < 4; ++row)
		{
			// For each column
			for (uint32 col = 0; col < 4; ++col)
			{
				float value = 0;

				// For each addition
				for (uint32 i = 0; i < 4; ++i)
				{
					// add them up
					value += lhs.Get(i, row) * rhs.Get(col, i);
				}

				// Assign it to the new matrix
				total.Set(col, row, value);
			}
		}

		// Return the product of the two matrices
		return total;
	}
	friend MATH_API FORCEINLINE Mat4& operator*=(Mat4& lhs, const Mat4& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}
	friend MATH_API FORCEINLINE Vec3 operator*(const Mat4& lhs, const Vec3& rhs)
	{
		Vec3 result;
		result.X = lhs.Get(0, 0) * rhs.X + lhs.Get(1, 0) * rhs.Y + lhs.Get(2, 0) * rhs.Z + lhs.Get(3, 0);
		result.Y = lhs.Get(0, 1) * rhs.X + lhs.Get(1, 1) * rhs.Y + lhs.Get(2, 1) * rhs.Z + lhs.Get(3, 1);
		result.Z = lhs.Get(0, 2) * rhs.X + lhs.Get(1, 2) * rhs.Y + lhs.Get(2, 2) * rhs.Z + lhs.Get(3, 2);

		return result;
	}
	friend MATH_API FORCEINLINE bool operator==(const Mat4& lhs, const Mat4& rhs)
	{
		for (uint32 i = 0; i < 16; ++i)
		{
			if (lhs[i] != rhs[i])
			{
				return false;
			}
		}

		return true;
	}
	friend MATH_API FORCEINLINE bool operator!=(const Mat4& lhs, const Mat4& rhs)
	{
		return !(lhs == rhs);
	}

	////////////////
	///   Data   ///
private:

	float _values[4][4];
};