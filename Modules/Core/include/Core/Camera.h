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

		REFLECTABLE
		EXTENDS(GameObject)

		//////////////////
		///   Fields   ///
	public:

		float VFOV = 60.f;
		float HFOV = 90.f;
		float ZMin = 0.1f;
		float ZMax = 100.f;

		///////////////////
		///   Methods   ///
	public:

		Mat4 GetPerspective() const;
	};
}