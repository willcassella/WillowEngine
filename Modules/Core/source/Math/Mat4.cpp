// Mat4.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Math/Mat4.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/PrimitiveInfo.h"

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