// FPSCamera.h
#pragma once

#include <Core\Camera.h>
#include "config.h"

namespace ExampleGame
{
	class EXAMPLEGAME_API FPSCamera : public Willow::Camera
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(Willow::Camera)

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