// Mat4.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Math/Mat4.h"

//////////////////////
///   Reflection   ///

STRUCT_REFLECTION(Mat4);

///////////////////
///   Methods   ///

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
	return String::Parse(string,
						 "[ @, @, @, @ ]\n"
						 "| @, @, @, @ |\n"
						 "| @, @, @, @ |\n"
						 "[ @, @, @, @ ]",
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

/////////////////////
///   Operators   ///

Mat4 operator*(const Mat4& lhs, const Mat4& rhs)
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