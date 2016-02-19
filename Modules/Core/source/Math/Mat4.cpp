// Mat4.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Math/Mat4.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/PrimitiveInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Mat4)
.IsStable();

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
