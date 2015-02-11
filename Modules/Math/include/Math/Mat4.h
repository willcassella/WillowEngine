// Mat4.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <cassert>
#include "Vec3.h"
#include "Quat.h"

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
	Mat4(float aa = 1.f, float ba = 0.f, float ca = 0.f, float da = 0.f,
			float ab = 0.f, float bb = 1.f, float cb = 0.f, float db = 0.f,
			float ac = 0.f, float bc = 0.f, float cc = 1.f, float dc = 0.f,
			float ad = 0.f, float bd = 0.f, float cd = 0.f, float dd = 1.f);

	///////////////////
	///   Methods   ///
public:

	/** Formats this Mat4 as a String */
	String ToString() const;

	/** Returns the inverse of this matrix */
	Mat4 Inverse() const;

	/** Parse a Mat4 from a String */
	static String FromString(Mat4& value, const String& string);

	/** Generates a perspective projection matrix with the given properties */
	static Mat4 Perspective(float hFOV, float vFOV, float zMin, float zMax);

	/** Generates a perspective projection matrix with the following horizontal FOV */
	static Mat4 PerspectiveHFOV(float hFOV, float ratio, float zMin, float zMax);

	/** Generates a perspective projection matrix with the following vertical FOV */
	static Mat4 PerspectiveVFOV(float vFOV, float ratio, float zMin, float zMax);

	/** Generates an orthographic projection matrix with the given properties */
	static Mat4 Orthographic(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);

	/** Generates a transformation matrix representing a translation */
	static Mat4 Translate(const Vec3& vec);

	/** Generates a transformation matrix representing a Scale */
	static Mat4 Scale(const Vec3& vec);

	/** Generates a transformation matrix representing a rotation */
	static Mat4 Rotate(const Quat& rot);

	/** Gets the value at the specified column and row */
	inline float Get(uint32 column, uint32 row) const
	{
		assert(column < 4 && row < 4);
		return _values[column][row];
	}

	/** Sets the value at the specified column and row */
	inline void Set(uint32 column, uint32 row, float value)
	{
		assert(column < 4 && row < 4);
		_values[column][row] = value;
	}

	/////////////////////
	///   Operators   ///
public:

	inline float* operator[](uint32 index)
	{
		assert(index < 16);
		return _values[index];
	}
	inline const float* operator[](uint32 index) const
	{
		assert(index < 16);
		return _values[index];
	}
	friend MATH_API Mat4 operator*(const Mat4& lhs, const Mat4& rhs);
	friend MATH_API Mat4& operator*=(Mat4& lhs, const Mat4& rhs);
	friend MATH_API Vec3 operator*(const Mat4& lhs, const Vec3& rhs);
	friend MATH_API bool operator==(const Mat4& lhs, const Mat4& rhs);
	friend MATH_API inline bool operator!=(const Mat4& lhs, const Mat4& rhs)
	{
		return !(lhs == rhs);
	}

	////////////////
	///   Data   ///
private:

	float _values[4][4];
};