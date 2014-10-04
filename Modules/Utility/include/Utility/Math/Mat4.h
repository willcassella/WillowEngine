// Mat4.h
#pragma once

#include <cassert>
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
		static Mat4 Perspective(float hFOV, float vFOV, float zMin, float zMax);
		static Mat4 PerspectiveHFOV(float hFOV, float ratio, float zMin, float zMax);
		static Mat4 PerspectiveVFOV(float vFOV, float ratio, float zMin, float zMax);
		static Mat4 Orthographic(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
		static Mat4 Translate(const Vec3& vec);
		static Mat4 Scale(const Vec3& vec);
		static Mat4 Rotate(const Quat& rot);
		inline float Get(uint32 column, uint32 row) const
		{ 
			assert(column < 4 && row < 4);
			return _values[column][row];
		}
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
		friend UTILITY_API Mat4 operator*(const Mat4& lhs, const Mat4& rhs);
		friend UTILITY_API Mat4& operator*=(Mat4& lhs, const Mat4& rhs);
		// @TODO: For now I'm assuming matrix - vector multiplication is commutative, but I really need to investigate that
		friend UTILITY_API Vec3 operator*(const Mat4& lhs, const Vec3& rhs);
		friend UTILITY_API Vec3 operator*(const Vec3& lhs, const Mat4& rhs);
		friend UTILITY_API Vec3& operator*=(Vec3& lhs, const Mat4& rhs);

		////////////////
		///   Data   ///
	private:

		float _values[4][4];
	};
}