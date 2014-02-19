#ifndef MAT4_H_
#define MAT4_H_

#include <cstdio>
#include <cmath>
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

	// Constructor, default sets to identity matrix
	Mat4(	const float aa = 1, const float ba = 0, const float ca = 0, const float da = 0,
			const float ab = 0, const float bb = 1, const float cb = 0, const float db = 0,
			const float ac = 0, const float bc = 0, const float cc = 1, const float dc = 0,
			const float ad = 0, const float bd = 0, const float cd = 0, const float dd = 1 );

	///////////////////
	///   Methods   ///
	///////////////////
public:

	// Returns the inverse of this matrix
	Mat4 inverse();

	// Print the matrix to the console
	void display() const;

	/////////////////////
	///   Rendering   ///
	/////////////////////
public:

	// Generates a perspective projection matrix
	static Mat4 perspective( const float hFOV, const float vFOV, const float zMin, const float zMax );

	// Generates a persepctive projection matrix based off desired horizontal FOV and screen ratio
	static Mat4 perspectiveHFOV( const float hFOV, const float ratio, const float zMin, const float zMax );

	// Generates a perspective projection matrix based off the desired vertical FOV and screen ratio
	static Mat4 perspectiveVFOV( const float vFOV, const float ratio, const float zMin, const float zMax );

	// Generates an orthographic projection matrix
	static Mat4 orthographic( const float xMin, const float xMax, const float yMin, const float yMax, const float zMin, const float zMax );

	// Returns a translation matrix from a 3-length vector
	static Mat4 translate( const Vec3& vec );

	// Returns a scale matrix from a 3-length vector
	static Mat4 scale( const Vec3& vec );

	// Returns a rotation matrix from a quaternion
	static Mat4 rotate( const Quat& rot );

	///////////////////////////////
	///   Getters and Setters   ///
	///////////////////////////////
public:

	// Get contents by row and column
	inline float get( const std::size_t column, const std::size_t row ) const
	{
		return values[column][row];
	}

	// Set contents by row and column
	inline void set( const std::size_t column, const std::size_t row, const float value )
	{
		values[column][row] = value;
	}

	/////////////////////
	///   Overloads   ///
	/////////////////////
public:

	// Multiply by another matrix
	Mat4 operator*( const Mat4& rhs );

	// Multiply by a 3-length vector
	Vec3 operator* ( const Vec3& rhs );

	// Get contents as an array
	inline float* operator[]( const std::size_t index )
	{
		return values[index];
	}

	// Get contents as a const array
	inline const float* const operator[]( const std::size_t index ) const
	{
		return values[index];
	}
};

#endif