// Camera.h
#pragma once

#include "GameObject.h"

namespace Engine
{
	class ENGINE_API Camera : public GameObject
	{
		///////////////////////
		///   Information   ///
	public:

		typedef GameObject Base;

		//////////////////
		///   Fields   ///
	public:

		float vFOV;
		float ratio;
		float zMin;
		float zMax;
		Math::Mat4 perspective;

		////////////////////////
		///   Constructors   ///
	public:

		Camera(const Willow::String& _name = "", float vFOV = 43, float ratio = 1280.0f / 720, float zMin = 0.1f, float zMax = 90);

		///////////////////
		///   Methods   ///
	public:

		void tick(float timeInterval) override;
		Math::Mat4 getPerspective();
	};
}