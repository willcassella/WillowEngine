// Camera.h
#pragma once

#include "GameObject.h"

namespace Willow
{
	class CORE_API Camera : public GameObject
	{
		///////////////////////
		///   Information   ///
	public:

		typedef GameObject Super;

		//////////////////
		///   Fields   ///
	public:

		float VFOV;
		float Ratio;
		float ZMin;
		float ZMax;

		////////////////////////
		///   Constructors   ///
	public:

		Camera(const String& name = "", float vFOV = 43.f, float ratio = 1280.f / 720.f, float zMin = 0.1f, float zMax = 90.f);

		///////////////////
		///   Methods   ///
	public:

		Mat4 GetPerspective() const;
	};
}