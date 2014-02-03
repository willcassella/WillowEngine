#ifndef MAT4_H_
#define MAT4_H_

#define DEG2RAD 0.0174532925f
#define RAD2DEG 57.2957795f

#include <stdio.h>
#include <math.h>
#include "Vec3.h"
#include "Quat.h"

// TODO: Add a lookat() function

struct Mat4
{
	////////////////
	///   Data   ///
	////////////////

private:

	// Matrix data members should never be accessed directly from outside
	float values[4][4];

	////////////////////////
	///   Constructors   ///
	////////////////////////

public:

	// Default constructor, sets to identity matrix
	Mat4()
	{
		// Column 1
		values[0][0] = 1; values[1][0] = 0; values[2][0] = 0; values[3][0] = 0;
		
		// Column 2
		values[0][1] = 0; values[1][1] = 1; values[2][1] = 0; values[3][1] = 0;
		
		// Column 3
		values[0][2] = 0; values[1][2] = 0; values[2][2] = 1; values[3][2] = 0;
		
		// Column 4
		values[0][3] = 0; values[1][3] = 0; values[2][3] = 0; values[3][3] = 1;
	}

	// Custom constructor
	Mat4(	float aa, float ba, float ca, float da,
			float ab, float bb, float cb, float db,
			float ac, float bc, float cc, float dc,
			float ad, float bd, float cd, float dd )
	{
		values[0][0] = aa; values[1][0] = ba; values[2][0] = ca; values[3][0] = da;
		values[0][1] = ab; values[1][1] = bb; values[2][1] = cb; values[3][1] = db;
		values[0][2] = ac; values[1][2] = bc; values[2][2] = cc; values[3][2] = dc;
		values[0][3] = ad; values[1][3] = bd; values[2][3] = cd; values[3][3] = dd;
	}

	///////////////////
	///   Methods   ///
	///////////////////

	// Returns the inverse of this matrix
	Mat4 inverse()
	{
		Mat4 result;

		// Seriously, fuck this shit, I had to type all this by hand
		// based off http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html

		///////////////////
		///  COLUMN 1   ///
		///////////////////

		/// ROW 1
		result.set( 0, 0,
		values[1][1]*values[2][2]*values[3][3] +
		values[2][1]*values[3][2]*values[1][3] +
		values[3][1]*values[1][2]*values[2][3] -
		values[1][1]*values[3][2]*values[2][3] -
		values[2][1]*values[1][2]*values[3][3] -
		values[3][1]*values[2][2]*values[1][3] );

		/// ROW 2
		result.set( 0, 1,
			values[0][1]*values[3][2]*values[2][3] +
			values[2][1]*values[0][2]*values[3][3] +
			values[3][1]*values[2][2]*values[0][3] -
			values[0][1]*values[2][2]*values[3][3] -
			values[2][1]*values[3][2]*values[0][3] -
			values[3][1]*values[0][2]*values[2][3] );

		/// ROW 3
		result.set( 0, 2,
			values[0][1]*values[1][2]*values[3][3] +
			values[1][1]*values[3][2]*values[0][3] +
			values[3][1]*values[0][2]*values[1][3] -
			values[0][1]*values[3][2]*values[1][3] -
			values[1][1]*values[0][2]*values[3][3] -
			values[3][1]*values[1][2]*values[0][3] );

		/// ROW 4 (fixed)
		result.set( 0, 3,
			values[0][1]*values[2][2]*values[1][3] +
			values[1][1]*values[0][2]*values[2][3] +
			values[2][1]*values[1][2]*values[0][3] -
			values[0][1]*values[1][2]*values[2][3] -
			values[1][1]*values[2][2]*values[0][3] -
			values[2][1]*values[0][2]*values[1][3] );

		////////////////////
		///   COLUMN 2   ///
		////////////////////

		/// ROW 1
		result.set( 1, 0,
			values[1][0]*values[3][2]*values[2][3] +
			values[2][0]*values[1][2]*values[3][3] +
			values[3][0]*values[2][2]*values[1][3] -
			values[1][0]*values[2][2]*values[3][3] -
			values[2][0]*values[3][2]*values[1][3] -
			values[3][0]*values[1][2]*values[2][3] );

		/// ROW 2
		result.set( 1, 1,
			values[0][0]*values[2][2]*values[3][3] +
			values[2][0]*values[3][2]*values[0][3] +
			values[3][0]*values[0][2]*values[2][3] -
			values[0][0]*values[3][2]*values[2][3] -
			values[2][0]*values[0][2]*values[3][3] -
			values[3][0]*values[2][2]*values[0][3] );

		/// ROW 3
		result.set( 1, 2,
			values[0][0]*values[3][2]*values[1][3] +
			values[1][0]*values[0][2]*values[3][3] +
			values[3][0]*values[1][2]*values[0][3] -
			values[0][0]*values[1][2]*values[3][3] -
			values[1][0]*values[3][2]*values[0][3] -
			values[3][0]*values[0][2]*values[1][3] );

		/// ROW 4
		result.set( 1, 3,
			values[0][0]*values[1][2]*values[2][3] +
			values[1][0]*values[2][2]*values[0][3] +
			values[2][0]*values[0][2]*values[1][3] -
			values[0][0]*values[2][2]*values[1][3] -
			values[1][0]*values[0][2]*values[2][3] -
			values[2][0]*values[1][2]*values[0][3] );

		////////////////////
		///   COLUMN 3   ///
		////////////////////

		/// ROW 1
		result.set( 2, 0,
			values[1][0]*values[2][1]*values[3][3] +
			values[2][0]*values[3][1]*values[1][3] +
			values[3][0]*values[1][1]*values[2][3] -
			values[1][0]*values[3][1]*values[2][3] -
			values[2][0]*values[1][1]*values[3][3] -
			values[3][0]*values[2][1]*values[1][3] );

		/// ROW 2
		result.set( 2, 1,
			values[0][0]*values[3][1]*values[2][3] +
			values[2][0]*values[0][1]*values[3][3] +
			values[3][0]*values[2][1]*values[0][3] -
			values[0][0]*values[2][1]*values[3][3] -
			values[2][0]*values[3][1]*values[0][3] -
			values[3][0]*values[0][1]*values[2][3] );

		/// ROW 3
		result.set( 2, 2,
			values[0][0]*values[1][1]*values[3][3] +
			values[1][0]*values[3][1]*values[0][3] +
			values[3][0]*values[0][1]*values[1][3] -
			values[0][0]*values[3][1]*values[1][3] -
			values[1][0]*values[0][1]*values[3][3] -
			values[3][0]*values[1][1]*values[0][3] );

		/// ROW 4
		result.set( 2, 3,
			values[0][0]*values[2][1]*values[1][3] +
			values[1][0]*values[0][1]*values[2][3] +
			values[2][0]*values[1][1]*values[0][3] -
			values[0][0]*values[1][1]*values[2][3] -
			values[1][0]*values[2][1]*values[0][3] -
			values[2][0]*values[0][1]*values[1][3] );

		////////////////////
		///   COLUMN 4   ///
		////////////////////

		/// ROW 1
		result.set( 3, 0,
			values[1][0]*values[3][1]*values[2][2] +
			values[2][0]*values[1][1]*values[3][2] +
			values[3][0]*values[2][1]*values[1][2] -
			values[1][0]*values[2][1]*values[3][2] -
			values[2][0]*values[3][1]*values[1][2] -
			values[3][0]*values[1][1]*values[2][2] );

		/// ROW 2
		result.set( 3, 1,
			values[0][0]*values[2][1]*values[3][2] +
			values[2][0]*values[3][1]*values[0][2] +
			values[3][0]*values[0][1]*values[2][2] -
			values[0][0]*values[3][1]*values[2][2] -
			values[2][0]*values[0][1]*values[3][2] -
			values[3][0]*values[2][1]*values[0][2] );

		/// ROW 3
		result.set( 3, 2,
			values[0][0]*values[3][1]*values[1][2] +
			values[1][0]*values[0][1]*values[3][2] +
			values[3][0]*values[1][1]*values[0][2] -
			values[0][0]*values[1][1]*values[3][2] -
			values[1][0]*values[3][1]*values[0][2] -
			values[3][0]*values[0][1]*values[1][2] );

		/// ROW 4
		result.set( 3, 3,
			values[0][0]*values[1][1]*values[2][2] +
			values[1][0]*values[2][1]*values[0][2] +
			values[2][0]*values[0][1]*values[1][2] -
			values[0][0]*values[2][1]*values[1][2] -
			values[1][0]*values[0][1]*values[2][2] -
			values[2][0]*values[1][1]*values[0][2] );

		return result;
	}

	// Print the matrix to the console
	void display()
	{
		// For each row
		for( int row = 0; row < 4; row++ )
		{
			printf("| ");
			
			// For each column
			for( int col = 0; col < 4; col++ )
			{
				// Print the value in that place
				printf( "%f  ", values[col][row] );
			}

			// Start a new line
			printf( " |\n" );
		}

		printf("\n\n\n");
	}

	/////////////////////
	///   Rendering   ///
	/////////////////////
	
	// Generates a perspective projection matrix
	static Mat4 perspective( float hFOV, float vFOV, float zMin, float zMax )
	{
		// Convert vertical and horizontal FOV to radians
		hFOV *= DEG2RAD;
		vFOV *= DEG2RAD;

		const float xMax = tanf( hFOV/2 ) * zMin;
		const float xMin = -xMax;

		const float yMax = tanf( vFOV/2 ) * zMin;
		const float yMin = -yMax;

		const float width = xMax - xMin;
		const float height = yMax - yMin;
		const float depth = zMax - zMin;
		
		return Mat4(
			2*zMin/width,	0,					(xMax+xMin)/width,		0,
			0,				2*zMin/height,		(yMax+yMin)/height,		0,
			0,				0,					-(zMax+zMin)/depth,		-2*zMax*zMin/depth,
			0,				0,					-1,						0 );
	}

	// Generates a persepctive projection matrix based off desired horizontal FOV and screen ratio
	static Mat4 perspectiveHFOV( float hFOV, float ratio, float zMin, float zMax )
	{
		// Convert hFOV to radians
		hFOV *= DEG2RAD;

		float vFOV = 2*atan( tan( hFOV/2 ) * 1/ratio );

		// Convert hFOV and vFOV back to degrees
		hFOV *= RAD2DEG;
		vFOV *= RAD2DEG;

		return perspective( hFOV, vFOV, zMin, zMax );
	}

	// Generates a perspective projection matrix based off the desired vertical FOV and screen ratio
	static Mat4 perspectiveVFOV( float vFOV, float ratio, float zMin, float zMax )
	{
		// Convert the vFOV to radians
		vFOV *= DEG2RAD;

		float hFOV = 2*atan( tan( vFOV/2 ) * ratio );

		// Convert hFOV and vFOV back to degrees
		hFOV *= RAD2DEG;
		vFOV *= RAD2DEG;

		return perspective( hFOV, vFOV, zMin, zMax );
	}

	// Generates an orthographic projection matrix
	static Mat4 orthographic( float xMin, float xMax, float yMin, float yMax, float zMin, float zMax )
	{
		const float width = xMax - xMin;
		const float height = yMax - yMin;
		const float depth = zMax - zMin;

		return Mat4( 
			2/width,	0,			0,			-(xMax+xMin)/width,
			0,			2/height,	0,			-(yMax+yMin)/height,
			0,			0,			-2/depth,	-(zMax+zMin)/depth,
			0,			0,			0,			1 );
	}

	// Returns a translation matrix from a 3-length vector
	static Mat4 translate( Vec3 vec )
	{
		return Mat4(
			1,	0,	0,	vec.x,
			0,	1,	0,	vec.y,
			0,	0,	1,	vec.z,
			0,	0,	0,	1	);
	}

	// Returns a scale matrix from a 3-length vector
	static Mat4 scale( Vec3 vec )
	{
		return Mat4(
			vec.x,	0,	0,	0,
			0,	vec.y,	0,	0,
			0,	0,	vec.z,	0,
			0,	0,	0,	1	);
	}

	// Returns a rotation matrix from a quaternion
	static Mat4 rotate( Quat rot )
	{
		// Retreive the data members of rot
		float x, y, z, w;
		rot.retrieve( &x, &y, &z, &w );
		
		return Mat4(
			1 - 2*y*y - 2*z*z,	2*x*y + 2*z*w,		2*x*z - 2*y*w,		0,
			2*x*y - 2*z*w,		1 - 2*x*x - 2*z*z,	2*y*z + 2*x*w,		0,
			2*x*z + 2*y*w,		2*y*z - 2*x*w,		1 - 2*x*x - 2*y*y,	0,
			0,					0,					0,					1 );
	}

	///////////////////////////////
	///   Getters and Setters   ///
	///////////////////////////////

	// Get contents by row and column
	float get( int column, int row )
	{
		return values[column][row];
	}

	// Set contents by row and column
	void set( int column, int row, float value )
	{
		values[column][row] = value;
	}

	/////////////////////
	///   Overloads   ///
	/////////////////////

	// Copy another matrix to this matrix
	void operator= (Mat4 rhs )
	{
		// For each column
		for( int col = 0; col < 4; col++ )
		{
			// For each row
			for( int row = 0; row < 4; row++ )
			{
				// Assign the corresponding value from the other matrix
				values[col][row] = rhs[col][row];
			}
		}
	}

	// Multiply by another matrix
	Mat4 operator* ( Mat4 rhs )
	{
		Mat4 total;

		// Cool algorithm I came up with for automatically doing this shit
		// Based off http://www.open.gl/transformations
		
		// For each row
		for( int row = 0; row < 4; row++ )
		{
			// For each column
			for( int col = 0; col < 4; col++ )
			{
				float value = 0;
				
				// For each addition
				for( int i = 0; i < 4; i++ )
				{
					// add them up
					value += values[i][row] * rhs[col][i];
				}

				// Assign it to the new matrix
				total.set( col, row, value );
			}
		}

		// Return the product of the two matrices
		return total;
	}

	// Multiply by a 3-length vector
	Vec3 operator* ( Vec3 rhs )
	{
		Vec3 result;
		result.x = values[0][0]*rhs.x + values[1][0]*rhs.y + values[2][0]*rhs.z + values[3][0];
		result.y = values[0][1]*rhs.x + values[1][1]*rhs.y + values[2][1]*rhs.z + values[3][1];
		result.z = values[0][2]*rhs.x + values[1][2]*rhs.y + values[2][2]*rhs.z + values[3][2];

		return result;
	}

	// Get contents as an array
	float* operator[]( int index )
	{
		return values[index];
	}
};

#endif