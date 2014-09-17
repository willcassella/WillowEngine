// Transform.h
#pragma once

#include <Utility\Math\Mat4.h>
#include "config.h"

namespace Willow
{
	namespace Mobility
	{
		enum Mobility
		{
			Static, 
			Moveable
		};
	}

	struct CORE_API Transform
	{
		//////////////////
		///   Fields   ///
	public:

		Vec3 Location;
		Quat Orientation;
		Vec3 Scale3D;
		// @TODO: encapsulate this better
		Transform* Parent;

	private:

		Mobility::Mobility _mobility;

		////////////////////////
		///   Constructors   ///
	public:

		Transform(Mobility::Mobility mobility = Mobility::Static, const Vec3& location = Vec3(), const Quat& orientation = Quat(), const Vec3& scale3D = Vec3(1.f, 1.f, 1.f));

		///////////////////
		///   Methods   ///
	public:

		Mobility::Mobility GetMobility() const;
		bool IsStatic() const;
		void Translate(const Vec3& vec, bool isLocal = true);
		void Scale(const Vec3& vec, bool isLocal = true);
		void Rotate(const Vec3& axis, float angle, bool isLocal = true);
		Mat4 GetTransfomationMatrix() const;
	};
}