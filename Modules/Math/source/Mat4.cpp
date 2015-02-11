// Mat4.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <cmath>
#include "../include/Math/Mat4.h"

const float Deg2Rad = 0.0174532925f;
const float Rad2Deg = 57.2957795f;

//////////////////////
///   Reflection   ///

STRUCT_REFLECTION(Mat4);

////////////////////////
///   Constructors   ///

Mat4::Mat4( float aa, float ba, float ca, float da,
			float ab, float bb, float cb, float db,
			float ac, float bc, float cc, float dc,
			float ad, float bd, float cd, float dd )
{
	this->_values[0][0] = aa; this->_values[1][0] = ba; this->_values[2][0] = ca; this->_values[3][0] = da;
	this->_values[0][1] = ab; this->_values[1][1] = bb; this->_values[2][1] = cb; this->_values[3][1] = db;
	this->_values[0][2] = ac; this->_values[1][2] = bc; this->_values[2][2] = cc; this->_values[3][2] = dc;
	this->_values[0][3] = ad; this->_values[1][3] = bd; this->_values[2][3] = cd; this->_values[3][3] = dd;
}

///////////////////
///   Methods   ///

String Mat4::ToString() const
{
	return String::Format("[ @, @, @, @ ]\n"
						  "| @, @, @, @ |\n"
						  "| @, @, @, @ |\n"
						  "[ @, @, @, @ ]",
						  _values[0][0], _values[1][0], _values[2][0], _values[3][0],
						  _values[0][1], _values[1][1], _values[2][1], _values[3][1],
						  _values[0][2], _values[1][2], _values[2][2], _values[3][2],
						  _values[0][3], _values[1][3], _values[2][3], _values[3][3]);
}

Mat4 Mat4::Inverse() const
{
	Mat4 result;

	///////////////////
	///  COLUMN 1   ///

	/// ROW 1
	result.Set( 0, 0,
		_values[1][1]*_values[2][2]*_values[3][3] +
		_values[2][1]*_values[3][2]*_values[1][3] +
		_values[3][1]*_values[1][2]*_values[2][3] -
		_values[1][1]*_values[3][2]*_values[2][3] -
		_values[2][1]*_values[1][2]*_values[3][3] -
		_values[3][1]*_values[2][2]*_values[1][3] );

	/// ROW 2
	result.Set( 0, 1,
		_values[0][1]*_values[3][2]*_values[2][3] +
		_values[2][1]*_values[0][2]*_values[3][3] +
		_values[3][1]*_values[2][2]*_values[0][3] -
		_values[0][1]*_values[2][2]*_values[3][3] -
		_values[2][1]*_values[3][2]*_values[0][3] -
		_values[3][1]*_values[0][2]*_values[2][3] );

	/// ROW 3
	result.Set( 0, 2,
		_values[0][1]*_values[1][2]*_values[3][3] +
		_values[1][1]*_values[3][2]*_values[0][3] +
		_values[3][1]*_values[0][2]*_values[1][3] -
		_values[0][1]*_values[3][2]*_values[1][3] -
		_values[1][1]*_values[0][2]*_values[3][3] -
		_values[3][1]*_values[1][2]*_values[0][3] );

	/// ROW 4
	result.Set( 0, 3,
		_values[0][1]*_values[2][2]*_values[1][3] +
		_values[1][1]*_values[0][2]*_values[2][3] +
		_values[2][1]*_values[1][2]*_values[0][3] -
		_values[0][1]*_values[1][2]*_values[2][3] -
		_values[1][1]*_values[2][2]*_values[0][3] -
		_values[2][1]*_values[0][2]*_values[1][3] );

	////////////////////
	///   COLUMN 2   ///

	/// ROW 1
	result.Set( 1, 0,
		_values[1][0]*_values[3][2]*_values[2][3] +
		_values[2][0]*_values[1][2]*_values[3][3] +
		_values[3][0]*_values[2][2]*_values[1][3] -
		_values[1][0]*_values[2][2]*_values[3][3] -
		_values[2][0]*_values[3][2]*_values[1][3] -
		_values[3][0]*_values[1][2]*_values[2][3] );

	/// ROW 2
	result.Set( 1, 1,
		_values[0][0]*_values[2][2]*_values[3][3] +
		_values[2][0]*_values[3][2]*_values[0][3] +
		_values[3][0]*_values[0][2]*_values[2][3] -
		_values[0][0]*_values[3][2]*_values[2][3] -
		_values[2][0]*_values[0][2]*_values[3][3] -
		_values[3][0]*_values[2][2]*_values[0][3] );

	/// ROW 3
	result.Set( 1, 2,
		_values[0][0]*_values[3][2]*_values[1][3] +
		_values[1][0]*_values[0][2]*_values[3][3] +
		_values[3][0]*_values[1][2]*_values[0][3] -
		_values[0][0]*_values[1][2]*_values[3][3] -
		_values[1][0]*_values[3][2]*_values[0][3] -
		_values[3][0]*_values[0][2]*_values[1][3] );

	/// ROW 4
	result.Set( 1, 3,
		_values[0][0]*_values[1][2]*_values[2][3] +
		_values[1][0]*_values[2][2]*_values[0][3] +
		_values[2][0]*_values[0][2]*_values[1][3] -
		_values[0][0]*_values[2][2]*_values[1][3] -
		_values[1][0]*_values[0][2]*_values[2][3] -
		_values[2][0]*_values[1][2]*_values[0][3] );

	////////////////////
	///   COLUMN 3   ///

	/// ROW 1
	result.Set( 2, 0,
		_values[1][0]*_values[2][1]*_values[3][3] +
		_values[2][0]*_values[3][1]*_values[1][3] +
		_values[3][0]*_values[1][1]*_values[2][3] -
		_values[1][0]*_values[3][1]*_values[2][3] -
		_values[2][0]*_values[1][1]*_values[3][3] -
		_values[3][0]*_values[2][1]*_values[1][3] );

	/// ROW 2
	result.Set( 2, 1,
		_values[0][0]*_values[3][1]*_values[2][3] +
		_values[2][0]*_values[0][1]*_values[3][3] +
		_values[3][0]*_values[2][1]*_values[0][3] -
		_values[0][0]*_values[2][1]*_values[3][3] -
		_values[2][0]*_values[3][1]*_values[0][3] -
		_values[3][0]*_values[0][1]*_values[2][3] );

	/// ROW 3
	result.Set( 2, 2,
		_values[0][0]*_values[1][1]*_values[3][3] +
		_values[1][0]*_values[3][1]*_values[0][3] +
		_values[3][0]*_values[0][1]*_values[1][3] -
		_values[0][0]*_values[3][1]*_values[1][3] -
		_values[1][0]*_values[0][1]*_values[3][3] -
		_values[3][0]*_values[1][1]*_values[0][3] );

	/// ROW 4
	result.Set( 2, 3,
		_values[0][0]*_values[2][1]*_values[1][3] +
		_values[1][0]*_values[0][1]*_values[2][3] +
		_values[2][0]*_values[1][1]*_values[0][3] -
		_values[0][0]*_values[1][1]*_values[2][3] -
		_values[1][0]*_values[2][1]*_values[0][3] -
		_values[2][0]*_values[0][1]*_values[1][3] );

	////////////////////
	///   COLUMN 4   ///

	/// ROW 1
	result.Set( 3, 0,
		_values[1][0]*_values[3][1]*_values[2][2] +
		_values[2][0]*_values[1][1]*_values[3][2] +
		_values[3][0]*_values[2][1]*_values[1][2] -
		_values[1][0]*_values[2][1]*_values[3][2] -
		_values[2][0]*_values[3][1]*_values[1][2] -
		_values[3][0]*_values[1][1]*_values[2][2] );

	/// ROW 2
	result.Set( 3, 1,
		_values[0][0]*_values[2][1]*_values[3][2] +
		_values[2][0]*_values[3][1]*_values[0][2] +
		_values[3][0]*_values[0][1]*_values[2][2] -
		_values[0][0]*_values[3][1]*_values[2][2] -
		_values[2][0]*_values[0][1]*_values[3][2] -
		_values[3][0]*_values[2][1]*_values[0][2] );

	/// ROW 3
	result.Set( 3, 2,
		_values[0][0]*_values[3][1]*_values[1][2] +
		_values[1][0]*_values[0][1]*_values[3][2] +
		_values[3][0]*_values[1][1]*_values[0][2] -
		_values[0][0]*_values[1][1]*_values[3][2] -
		_values[1][0]*_values[3][1]*_values[0][2] -
		_values[3][0]*_values[0][1]*_values[1][2] );

	/// ROW 4
	result.Set( 3, 3,
		_values[0][0]*_values[1][1]*_values[2][2] +
		_values[1][0]*_values[2][1]*_values[0][2] +
		_values[2][0]*_values[0][1]*_values[1][2] -
		_values[0][0]*_values[2][1]*_values[1][2] -
		_values[1][0]*_values[0][1]*_values[2][2] -
		_values[2][0]*_values[1][1]*_values[0][2] );

	return result;
}

//bool gluInvertMatrix( const double m[16], double invOut[16] ) {
//    double inv[16], det;
//    int i;
//
//    inv[0] = m[5]  * m[10] * m[15] - 
//             m[5]  * m[11] * m[14] - 
//             m[9]  * m[6]  * m[15] + 
//             m[9]  * m[7]  * m[14] +
//             m[13] * m[6]  * m[11] - 
//             m[13] * m[7]  * m[10];
//
//    inv[4] = -m[4]  * m[10] * m[15] + 
//              m[4]  * m[11] * m[14] + 
//              m[8]  * m[6]  * m[15] - 
//              m[8]  * m[7]  * m[14] - 
//              m[12] * m[6]  * m[11] + 
//              m[12] * m[7]  * m[10];
//
//    inv[8] = m[4]  * m[9] * m[15] - 
//             m[4]  * m[11] * m[13] - 
//             m[8]  * m[5] * m[15] + 
//             m[8]  * m[7] * m[13] + 
//             m[12] * m[5] * m[11] - 
//             m[12] * m[7] * m[9];
//
//    inv[12] = -m[4]  * m[9] * m[14] + 
//               m[4]  * m[10] * m[13] +
//               m[8]  * m[5] * m[14] - 
//               m[8]  * m[6] * m[13] - 
//               m[12] * m[5] * m[10] + 
//               m[12] * m[6] * m[9];
//
//    inv[1] = -m[1]  * m[10] * m[15] + 
//              m[1]  * m[11] * m[14] + 
//              m[9]  * m[2] * m[15] - 
//              m[9]  * m[3] * m[14] - 
//              m[13] * m[2] * m[11] + 
//              m[13] * m[3] * m[10];
//
//    inv[5] = m[0]  * m[10] * m[15] - 
//             m[0]  * m[11] * m[14] - 
//             m[8]  * m[2] * m[15] + 
//             m[8]  * m[3] * m[14] + 
//             m[12] * m[2] * m[11] - 
//             m[12] * m[3] * m[10];
//
//    inv[9] = -m[0]  * m[9] * m[15] + 
//              m[0]  * m[11] * m[13] + 
//              m[8]  * m[1] * m[15] - 
//              m[8]  * m[3] * m[13] - 
//              m[12] * m[1] * m[11] + 
//              m[12] * m[3] * m[9];
//
//    inv[13] = m[0]  * m[9] * m[14] - 
//              m[0]  * m[10] * m[13] - 
//              m[8]  * m[1] * m[14] + 
//              m[8]  * m[2] * m[13] + 
//              m[12] * m[1] * m[10] - 
//              m[12] * m[2] * m[9];
//
//    inv[2] = m[1]  * m[6] * m[15] - 
//             m[1]  * m[7] * m[14] - 
//             m[5]  * m[2] * m[15] + 
//             m[5]  * m[3] * m[14] + 
//             m[13] * m[2] * m[7] - 
//             m[13] * m[3] * m[6];
//
//    inv[6] = -m[0]  * m[6] * m[15] + 
//              m[0]  * m[7] * m[14] + 
//              m[4]  * m[2] * m[15] - 
//              m[4]  * m[3] * m[14] - 
//              m[12] * m[2] * m[7] + 
//              m[12] * m[3] * m[6];
//
//    inv[10] = m[0]  * m[5] * m[15] - 
//              m[0]  * m[7] * m[13] - 
//              m[4]  * m[1] * m[15] + 
//              m[4]  * m[3] * m[13] + 
//              m[12] * m[1] * m[7] - 
//              m[12] * m[3] * m[5];
//
//    inv[14] = -m[0]  * m[5] * m[14] + 
//               m[0]  * m[6] * m[13] + 
//               m[4]  * m[1] * m[14] - 
//               m[4]  * m[2] * m[13] - 
//               m[12] * m[1] * m[6] + 
//               m[12] * m[2] * m[5];
//
//    inv[3] = -m[1] * m[6] * m[11] + 
//              m[1] * m[7] * m[10] + 
//              m[5] * m[2] * m[11] - 
//              m[5] * m[3] * m[10] - 
//              m[9] * m[2] * m[7] + 
//              m[9] * m[3] * m[6];
//
//    inv[7] = m[0] * m[6] * m[11] - 
//             m[0] * m[7] * m[10] - 
//             m[4] * m[2] * m[11] + 
//             m[4] * m[3] * m[10] + 
//             m[8] * m[2] * m[7] - 
//             m[8] * m[3] * m[6];
//
//    inv[11] = -m[0] * m[5] * m[11] + 
//               m[0] * m[7] * m[9] + 
//               m[4] * m[1] * m[11] - 
//               m[4] * m[3] * m[9] - 
//               m[8] * m[1] * m[7] + 
//               m[8] * m[3] * m[5];
//
//    inv[15] = m[0] * m[5] * m[10] - 
//              m[0] * m[6] * m[9] - 
//              m[4] * m[1] * m[10] + 
//              m[4] * m[2] * m[9] + 
//              m[8] * m[1] * m[6] - 
//              m[8] * m[2] * m[5];
//
//    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
//
//    if (det == 0)
//        return false;
//
//    det = 1.0 / det;
//
//    for (i = 0; i < 16; i++)
//        invOut[i] = inv[i] * det;
//
//    return true;
//}

String Mat4::FromString(Mat4& value, const String& string)
{
	return String::Parse("[ @, @, @, @ ]\n"
						 "| @, @, @, @ |\n"
						 "| @, @, @, @ |\n"
						 "[ @, @, @, @ ]", string,
						 value._values[0][0], value._values[1][0], value._values[2][0], value._values[3][0],
						 value._values[0][1], value._values[1][1], value._values[2][1], value._values[3][1],
						 value._values[0][2], value._values[1][2], value._values[2][2], value._values[3][2],
						 value._values[0][3], value._values[1][3], value._values[2][3], value._values[3][3]);
}

Mat4 Mat4::Perspective(float hFOV, float vFOV, float zMin, float zMax)
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
		2*zMin/width,	0,					(xMax+xMin)/width,		0,
		0,				2*zMin/height,		(yMax+yMin)/height,		0,
		0,				0,					-(zMax+zMin)/depth,		-2*zMax*zMin/depth,
		0,				0,					-1,						0 );
}

Mat4 Mat4::PerspectiveHFOV(float hFOV, float ratio, float zMin, float zMax)
{
	// Convert hFOV to radians
	float RadHFOV = hFOV * Deg2Rad; // @TODO: RadHOV is unused, is that a bug or a typo?
	float vFOV = Rad2Deg * 2 * atan(tan(hFOV * 0.5f) * 1/ratio);

	return Perspective(hFOV, vFOV, zMin, zMax);
}

Mat4 Mat4::PerspectiveVFOV(float vFOV, float ratio, float zMin, float zMax)
{
	// Convert the vFOV to radians
	float RadVFOV = vFOV * Deg2Rad;
	float hFOV = Rad2Deg * 2 * atan(tan(RadVFOV * 0.5f) * ratio);

	return Perspective(hFOV, vFOV, zMin, zMax);
}

Mat4 Mat4::Orthographic(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	float width = xMax - xMin;
	float height = yMax - yMin;
	float depth = zMax - zMin;

	return Mat4( 
		2/width,	0,			0,			-(xMax + xMin) / width,
		0,			2/height,	0,			-(yMax + yMin) / height,
		0,			0,			-2 / depth,	-(zMax + zMin) / depth,
		0,			0,			0,			1 );
}

Mat4 Mat4::Translate(const Vec3& vec)
{
	return Mat4(
		1,	0,	0,	vec.X,
		0,	1,	0,	vec.Y,
		0,	0,	1,	vec.Z,
		0,	0,	0,	1 );
}

Mat4 Mat4::Scale(const Vec3& vec)
{
	return Mat4(
		vec.X,	0,	0,	0,
		0,	vec.Y,	0,	0,
		0,	0,	vec.Z,	0,
		0,	0,	0,	1	);
}

Mat4 Mat4::Rotate(const Quat& rot)
{
	float x, y, z, w;
	x = rot.X;
	y = rot.Y;
	z = rot.Z;
	w = rot.W;

	return Mat4(
		1 - 2*y*y - 2*z*z,	2*x*y + 2*z*w,		2*x*z - 2*y*w,		0,
		2*x*y - 2*z*w,		1 - 2*x*x - 2*z*z,	2*y*z + 2*x*w,		0,
		2*x*z + 2*y*w,		2*y*z - 2*x*w,		1 - 2*x*x - 2*y*y,	0,
		0,					0,					0,					1 );
}

/////////////////////
///   Operators   ///

Mat4 operator*(const Mat4& lhs, const Mat4& rhs)
{
	Mat4 total;

	// For each row
	for(uint32 row = 0; row < 4; ++row) 
	{
		// For each column
		for(uint32 col = 0; col < 4; ++col) 
		{
			float value = 0;

			// For each addition
			for(uint32 i = 0; i < 4; ++i) 
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

Mat4& operator*=(Mat4& lhs, const Mat4& rhs)
{
	lhs = lhs * rhs;
	return lhs;
}

Vec3 operator*(const Mat4& lhs, const Vec3& rhs)
{
	Vec3 result;
	result.X = lhs.Get(0, 0) * rhs.X + lhs.Get(1, 0) * rhs.Y + lhs.Get(2, 0) * rhs.Z + lhs.Get(3, 0);
	result.Y = lhs.Get(0, 1) * rhs.X + lhs.Get(1, 1) * rhs.Y + lhs.Get(2, 1) * rhs.Z + lhs.Get(3, 1);
	result.Z = lhs.Get(0, 2) * rhs.X + lhs.Get(1, 2) * rhs.Y + lhs.Get(2, 2) * rhs.Z + lhs.Get(3, 2);

	return result;
}

bool operator==(const Mat4& lhs, const Mat4& rhs)
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