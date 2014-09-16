// Mat4.h
#pragma once

#include "Vec3.h"
#include "Quat.h"

namespace Willow
{
	struct UTILITY_API Mat4
	{
		////////////////////////
		///   Constructors   ///
	public:

		Mat4(float aa = 1, float ba = 0, float ca = 0, float da = 0,
			 float ab = 0, float bb = 1, float cb = 0, float db = 0,
			 float ac = 0, float bc = 0, float cc = 1, float dc = 0,
			 float ad = 0, float bd = 0, float cd = 0, float dd = 1);

		///////////////////
		///   Methods   ///
	public:

		Mat4 Inverse() const;
		// Print the matrix to the console @TODO: Replace this with a << operator overload
		void Display() const;
		static Mat4 Perspective(float hFOV, float vFOV, float zMin, float zMax);
		static Mat4 PerspectiveHFOV(float hFOV, float ratio, float zMin, float zMax);
		static Mat4 PerspectiveVFOV(float vFOV, float ratio, float zMin, float zMax);
		static Mat4 Orthographic(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
		static Mat4 Translate(const Vec3& vec);
		static Mat4 Scale(const Vec3& vec);
		static Mat4 Rotate(const Quat& rot);
		inline float Get(uint32 column, uint32 row) const
		{
			return _values[column][row];
		}
		inline void Set(uint32 column, uint32 row, float value)
		{
			_values[column][row] = value;
		}

		/////////////////////
		///   Operators   ///
	public:

		Mat4 operator*(const Mat4& rhs) const;
		Vec3 operator* (const Vec3& rhs) const;
		inline float* operator[](uint32 index)
		{
			return _values[index];
		}
		inline const float* operator[](uint32 index) const
		{
			return _values[index];
		}

		////////////////
		///   Data   ///
	private:

		float _values[4][4];
	};
}