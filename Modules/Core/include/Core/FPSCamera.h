// FPSCamera.h
#pragma once

#include "Camera.h"

namespace TestGame
{
	class CORE_API FPSCamera : public Willow::Camera
	{
		///////////////////////
		///   Information   ///
	public:

		typedef Willow::Camera Super;

		////////////////////////
		///   Constructors   ///
	public:

		FPSCamera(const Willow::String& name = "", float vFOV = 43.f, float ratio = 1280.f / 720.f, float zMin = 0.1f, float zMax = 90.f);

		///////////////////
		///   Actions   ///
	public:

		void MoveForward(float value);
		void MoveRight(float value);
		void LookUp(float value);
		void LookRight(float value);
	};
}