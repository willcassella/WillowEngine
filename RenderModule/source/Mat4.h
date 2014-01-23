#ifndef MAT4_H_
#define MAT4_H_

#include <stdio.h>
#include <glm\gtc\matrix_transform.hpp>

struct Mat4
{
	// Data
	float values[4][4];

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

	//// Returns the inverse of this matrix
	//Mat4 inverse()
	//{
	//	
	//}

	// Get contents as an array
	float* operator[]( int index )
	{
		return values[index];
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
				// Row and column must be reversed because of how the data is stored, i might change this
				total.set( row, col, value );
			}
		}

		// Return the product of the two matrices
		return total;
	}

	// Assign to values from another matrix
	Mat4 operator= (Mat4 rhs )
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

	// Print the matrix to the console (for debugging, to be removed)
	void display()
	{
		// For each column
		for( int col = 0; col < 4; col++ )
		{
			// For each row
			for( int row = 0; row < 4; row++ )
			{
				printf( "%f  ", values[col][row] );
			}

			printf( "\n" );
		}

		printf("\n\n\n");
	}

	///////////////////////
	//// FOR DEBUGGING ////
	///////////////////////

	glm::mat4 to_glm()
	{
		return glm::mat4(
			values[0][0], values[1][0], values[2][0], values[3][0],
			values[0][1], values[1][1], values[2][1], values[3][1],
			values[0][2], values[1][2], values[2][2], values[3][2],
			values[0][3], values[1][3], values[2][3], values[3][3] );
	}

	void set_from_glm( glm::mat4 mat )
	{
		// For each column
		for( int col = 0; col < 4; col++ )
		{
			// For each row
			for( int row = 0; row < 4; row++ )
			{
				// Assign from the corresponding value in the GLM matrix
				values[col][row] = mat[col][row];
			}
		}
	}
};

#endif