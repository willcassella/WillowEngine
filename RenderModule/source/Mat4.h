#ifndef MAT4_H_
#define MAT4_H_

struct Mat4
{
	// Data
	float values[4][4];

	// Default constructor, sets to identity matrix
	Mat4()
	{
		// Row 1
		values[0][0] = 1; values[0][1] = 0; values[0][2] = 0; values[0][3] = 0;
		
		// Row 2
		values[1][0] = 0; values[1][1] = 1; values[1][2] = 0; values[1][3] = 0;
		
		// Row 3
		values[2][0] = 0; values[2][1] = 0; values[2][2] = 1; values[2][3] = 0;
		
		// Row 4
		values[3][0] = 0; values[3][1] = 0; values[3][2] = 0; values[3][3] = 1;
	}

	// Custom constructor
	Mat4(	float aa, float ab, float ac, float ad,
			float ba, float bb, float bc, float bd,
			float ca, float cb, float cc, float cd,
			float da, float db, float dc, float dd )
	{
		values[0][0] = aa; values[0][1] = ab; values[0][2] = ac; values[0][3] = ad;
		values[1][0] = ba; values[1][1] = bb; values[1][2] = bc; values[1][3] = bd;
		values[2][0] = ca; values[2][1] = cb; values[2][2] = cc; values[2][3] = cd;
		values[3][0] = da; values[3][1] = db; values[3][2] = dc; values[3][3] = dd;
	}

	// Get contents by row and column
	float get( int row, int column )
	{
		return values[row][column];
	}

	// Set contents by row and column
	void set( int row, int column, float value )
	{
		values[row][column] = value;
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
		// based off http://www.open.gl/transformations
		
		// For each row
		for( int row = 0; row < 4; row++ )
		{
			// For each column
			for( int col = 0; col < 4; col++ )
			{
				int value = 0;
				
				// For each addition
				for( int i = 0; i < 4; i++ )
				{
					// add them up
					value += values[row][i] * rhs[i][col];
				}

				// Assign it to the new matrix
				total.set( row, col, value );
			}
		}
	}
};

#endif