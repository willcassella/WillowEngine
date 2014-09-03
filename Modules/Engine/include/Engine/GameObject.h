// GameObject.h
#pragma once

#include <Utility\String.h>
#include <Utility\Math\Transform.h>
#include "config.h"

namespace Engine
{
	class ENGINE_API GameObject
	{
		//////////////////
		///   Fields   ///
	public:

		Willow::String name;
		Math::Transform transform;

		////////////////////////
		///   Constructors   ///
	public:

		GameObject(const Willow::String& _name = "");

		///////////////////
		///   Methods   ///
	public:

		virtual void tick(float timeInterval) = 0;
	};
}