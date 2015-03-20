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

		FPSCamera();

		///////////////////
		///   Actions   ///
	public:

		void MoveForward(float value);
		void MoveRight(float value);
		void LookUp(float value);
		void LookRight(float value);
	};
}