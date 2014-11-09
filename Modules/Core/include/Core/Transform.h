// Transform.h
#pragma once

#include <Utility\Math\Mat4.h>
#include "config.h"

namespace Willow
{
	enum class Mobility
	{
		Static, 
		Moveable
	};

	class CORE_API Transform : public object
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(object)

		//////////////////
		///   Fields   ///
	public:

		Vec3 Location;
		Quat Orientation;
		Vec3 Scale3D;
		// @TODO: encapsulate this better
		Transform* Parent;

	private:

		Mobility _mobility;

		////////////////////////
		///   Constructors   ///
	public:

		Transform(Mobility mobility = Mobility::Static, const Vec3& location = Vec3(), const Quat& orientation = Quat(), const Vec3& scale3D = Vec3(1.f, 1.f, 1.f));

		///////////////////
		///   Methods   ///
	public:

		Mobility GetMobility() const;
		bool IsStatic() const;
		void Translate(const Vec3& vec, bool isLocal = true);
		void Scale(const Vec3& vec, bool isLocal = true);
		void Rotate(const Vec3& axis, float angle, bool isLocal = true);
		Mat4 GetTransfomationMatrix() const;
	};
}